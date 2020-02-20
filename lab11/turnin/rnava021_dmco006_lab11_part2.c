/*	Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 11  Exercise 2
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
task tasks[1];
const unsigned short tasksNum = 1;

/* information held constant */
const unsigned long periodLcdDisplay = 500;
const unsigned long periodGCD = 500;

const unsigned char string[] = "CS120B is Legend... wait for it DARY";
const unsigned char size = 36;

/* helper functions */
void substring(unsigned char i) {
	unsigned char sub[size];
	unsigned char j;
	
	for (j = 0; (j < 16) && (i < size); i++, j++) {
		sub[j] = string[i];
	}
	if (j < 16) {
		for ( ; j < 16; j++) {
			sub[j] = ' ';
		}
	}
	
	LCD_DisplayString(1, sub);
}

/* lcdDisplay_SM */
enum LD_States {LC};
int lcdDisplay_SM (int state) {
	static unsigned char start_char = 0;
	
	switch (state) { // transitions
		case LC:
			state = LC;
			break;
		default:
			state = LC;
			break;
	} // transitions
	switch (state) { // actions
		case LC:
			substring(start_char);
			start_char++;
			
			if (start_char == size) {
				start_char = 0;
			}
			
			break;
		default:
			break;
	} // actions
	return state;
}

int main(void) {
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	unsigned int i = 0;
	
	tasks[i].state = LC;
	tasks[i].period = periodLcdDisplay;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &lcdDisplay_SM;
	i++;

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