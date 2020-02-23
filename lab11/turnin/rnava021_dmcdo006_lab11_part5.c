/*	Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 11  Exercise 5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "header/timer.h"
#include "header/io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag;

#include <bit.h>
/* A struct to collect all items related to a task. */
typedef struct task {
	int state;                  // Task's current state
	unsigned long period;       // Task period
	unsigned long elapsedTime;  // Time elapsed since last task tick
	int (*TickFct)(int);        // Task tick function
} task;

/* array to hold tasks */
task tasks[3];
const unsigned short tasksNum = 3;

/* information held constant */
const unsigned long periodGCD = 20;
const unsigned long periodPauseButton = 20;
const unsigned long periodGame = 20;
const unsigned long periodLCDDisplay = 20;

const unsigned char go_message[] = "GAME  OVER";

/* shared variables */
unsigned short upperObst;
unsigned short lowerObst;
unsigned char pos;
unsigned char game_state;
unsigned char pause;

/* helper functions */
void UpdateObst(){
	upperObst = upperObst << 1;
	lowerObst = lowerObst << 1;
	if(!upperObst){upperObst = 0x0001;}
	if(!lowerObst){lowerObst = 0x0001;}
}

void UpdateDisplay(){
	unsigned char lcd_i;
	unsigned short upper = upperObst;
	unsigned short lower = lowerObst;
	//Updates Obstacles on the screen by determining their positions
	lcd_i = 1;
	while(lcd_i <= 16){
		if(upper & 0x8000){//IF first bit is 1
			LCD_Cursor(lcd_i);// go to found postion
			LCD_WriteData('#');//write the obstacle in.
		}
		upper = upper << 1;//shift to the left
		lcd_i++;//shift value
	}
	lcd_i = 1;
	while(lcd_i <= 16){
		if(lower & 0x8000){
			LCD_Cursor(lcd_i + 16);
			LCD_WriteData('#');
		}
		lower = lower << 1;
		lcd_i++;
	}
	//Update/reset cursor position
	if(pos){
		LCD_Cursor(17);
	}
	else{
		LCD_Cursor(1);
	}

}

/* pauseButton_SM */
enum PB_States{PB_start, PB_wait, PB_press, PB_release};
int pauseButton_SM (int state){
	unsigned char pbutton = (~PINA & 0x01);
	switch(state){//Transitions
		case PB_start:
			pause = 0;
			state = PB_wait;
			break;
		case PB_wait:
			state = (pbutton) ? PB_press : PB_wait;
			break;
		case PB_press:
			state = PB_release;
			break;
		case PB_release:
			state = (pbutton) ? PB_release : PB_wait;
			break;
		default:
			state = PB_start;
			break;
	}
	switch(state){//Actions
		case PB_start:
			break;
		case PB_wait:
			pause = 0;
			break;
		case PB_press:
			pause = 1;
			break;
		case PB_release:
		    pause = 0;
			break;
		default:
			break;
	}
	return state;
}

/* GameSM */
enum G_States{G_start, G_init, G_play, G_pause, G_gameover};
int GameSM(int state){
	static unsigned char game_over;
	static unsigned char i;
	unsigned char upbutton = (~PINA & 0x02) >> 1;
	unsigned char downbutton = (~PINA & 0x03) >> 2;
	switch(state){//Transitions
		case G_start:
			state = G_init;
			break;
		case G_init://Don't get confused.
			state = (pause) ? G_play : G_init;
			break;
		case G_play:
			if(!(game_over || pause)){
				state = G_play;
			}
			else if(game_over){
				state = G_gameover;
			}
			else if(pause && !game_over){
				state = G_pause;
			}
			else{state = G_play;}//Error. Should not occur
			break;
		case G_pause:
			state = (pause) ? G_play : G_pause;
			break;
		case G_gameover:
			state = (pause) ? G_play : G_gameover;
			break;
		default:
			state = G_start;
			break;
	}
	switch(state){//Actions
		case G_start:
			break;
		case G_init://Don't get confused.
			i = 0;
			game_over = 0;
			pos = 0;
			upperObst = 0x0040;
			lowerObst = 0x0004;
			game_state = 0;
			break;
		case G_play:
			//Update Obstacles
			i++;
			game_state = 0;
			if(i > 5){
				i = 0;
				UpdateObst();
			}
			//Check for a Game Over
			if(pos == 0 && upperObst == 0x8000){
				game_over = 1;
			}
			if(pos == 1 && upperObst == 0x8000){
				game_over = 1;
			}
			//Update player char position
			if((!downbutton) && upbutton){
				pos = 0;
			}
			else if((!upbutton) && downbutton){
				pos = 1;
			}
			break;
		case G_pause:
			i = 0;
			break;
		case G_gameover:
			i = 0;
			game_over = 0;
			upperObst = 0x0040;
			lowerObst = 0x0004;
			pos = 0;
			game_state = 1;
			break;
		default:
			break;
	}
	return state;
}

/* LCDDisplaySM */
enum LD_States{LD_start, LD_display};
int LCDDisplaySM(int state){
	static unsigned char message_done = 0;
	switch(state){//Transitions
		case LD_start:
			state = LD_display;
			break;
		case LD_display:
			state = LD_display;
			break;
		default:
			state = LD_display;
			break;
	}
	switch(state){//Actions
		case LD_start:
			break;
		case LD_display:
			if(game_state){
				LCD_ClearScreen();
				LCD_DisplayString(4, go_message);
			}
			else{
				LCD_ClearScreen();
				UpdateDisplay();
			}
			
			break;
		default:
			break;
	}
	return state;
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	unsigned int i = 0;
	
	tasks[i].state = PB_start;
	tasks[i].period = periodPauseButton;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &pauseButton_SM;
	i++;

	tasks[i].state = G_start;
	tasks[i].period = periodGame;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &GameSM;
	i++;

	tasks[i].state = LD_start;
	tasks[i].period = periodLCDDisplay;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &LCDDisplaySM;

	TimerSet(periodGCD);
	TimerOn();
	LCD_init();
	
	while (1) {
		for (i = 0; i < tasksNum; i++) {
			if (tasks[i].elapsedTime >= tasks[i].period) {
				tasks[i].state = tasks[i].TickFct(tasks[i].state);
				tasks[i].elapsedTime = 0;
			}
			tasks[i].elapsedTime += periodGCD;
		}
		while (!TimerFlag) {}
		TimerFlag = 0;
	}
	
    return 0;
}