/*	Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 11  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include "header/bit.h"
#include "header/timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag;

/* keypad implementation */
unsigned char GetKeypadKey() {
    PORTC = 0xEF; // ROW4
	asm("nop");
	if (GetBit(PINC, 0) == 0) { return 'D'; } // COL4
	if (GetBit(PINC, 1) == 0) { return '#'; } // COL3
	if (GetBit(PINC, 2) == 0) { return '0'; } // COL2
	if (GetBit(PINC, 3) == 0) { return '*'; } // COL1
		
	PORTC = 0xDF; // R0W3
	asm("nop");
	if (GetBit(PINC, 0) == 0) { return 'C'; } // COL4
	if (GetBit(PINC, 1) == 0) { return '9'; } // COL3
	if (GetBit(PINC, 2) == 0) { return '8'; } // COL2
	if (GetBit(PINC, 3) == 0) { return '7'; } // COL1
		
	PORTC = 0xBF; // R0W2
	asm("nop");
	if (GetBit(PINC, 0) == 0) { return 'B'; } // COL4
	if (GetBit(PINC, 1) == 0) { return '6'; } // COL3
	if (GetBit(PINC, 2) == 0) { return '5'; } // COL2
	if (GetBit(PINC, 3) == 0) { return '4'; } // COL1
		
	PORTC = 0x7F; // R0W1
	asm("nop");
	if (GetBit(PINC, 0) == 0) { return 'A'; } // COL4
	if (GetBit(PINC, 1) == 0) { return '3'; } // COL3
	if (GetBit(PINC, 2) == 0) { return '2'; } // COL2
	if (GetBit(PINC, 3) == 0) { return '1'; } // COL1

    return '\0';
}

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
const unsigned long periodKeypadInput = 10;
const unsigned long periodSelectOutput = 10;
const unsigned long periodCombine = 10;
const unsigned long periodGCD = 10;

/* shared variables */
unsigned char input;
unsigned char output;

/* keypadInput_SM */
enum KI_States {KI};
int keypadInput_SM (int state) {
	switch (state) { // transitions
	case KI:
		state = KI;
		break;
	default:
		state = KI;
		break;
	} // transitions
	switch (state) { // actions
		case KI:
			input = GetKeypadKey();
			break;
		default:
			break;
	} // actions
	return state;
}

/* selectOutput_SM */
enum SO_States {SO};
int selectOutput_SM (int state) {
	switch (state) { // transitions
		case SO:
			state = SO;
			break;
		default:
			state = SO;
			break;
	} // transitions
	switch (state) { // actions
		case SO:
			switch (input) {
				case '\0': output = 0x1F; break;
				case '1': output = 0x01; break;
				case '2': output = 0x02; break;
				case '3': output = 0x03; break;
				case '4': output = 0x04; break;
				case '5': output = 0x05; break;
				case '6': output = 0x06; break;
				case '7': output = 0x07; break;
				case '8': output = 0x08; break;
				case '9': output = 0x09; break;
				case 'A': output = 0x0A; break;
				case 'B': output = 0x0B; break;
				case 'C': output = 0x0C; break;
				case 'D': output = 0x0D; break;
				case '*': output = 0x0E; break;
				case '0': output = 0x00; break;
				case '#': output = 0x0F; break;
				default: output = 0x1B; break;
			}
			break;
		default:
			break;
	} // actions
	return state;
}

/* combine_SM */
enum C_SM {C_state};
int combine_SM (int state) {
	unsigned char out;
	
	switch (state) { // transitions
		case C_state:
			state = C_state;
			break;
		default:
			state = C_state;
			break;
	} // transitions
	switch (state) { // actions
		case C_state:
			out = output;
			break;
		default:
			out = output;
			break;
	}
	PORTB = out;
	return state;
}

int main(void) {
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	
	unsigned int i = 0;
	tasks[i].state = KI;
	tasks[i].period = periodKeypadInput;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &keypadInput_SM;
	i++;
	
	tasks[i].state = SO;
	tasks[i].period = periodSelectOutput;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &selectOutput_SM;
	i++;

	tasks[i].state = C_state;
	tasks[i].period = periodCombine;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &combine_SM;
	i++;
	
	TimerSet(periodGCD);
	TimerOn();
	
	while (1) {
		for (i = 0; i < tasksNum; i++) {
			if (tasks[i].elapsedTime >= tasks[i].period) {
				tasks[i].state = tasks[i].TickFct(tasks[i].state);
				tasks[i].elapsedTime = 0;
			}
			tasks[i].elapsedTime += periodGCD;
		}
		while (!TimerFlag) { }
		TimerFlag = 0;
	}
	
    return 0;
}
