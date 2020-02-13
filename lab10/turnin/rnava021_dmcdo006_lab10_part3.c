/*	Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 10  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

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
const unsigned long tasksPeriodGCD = 2;
const unsigned long periodThreeLEDs = 300;
const unsigned long periodBlinkingLED = 1000;
const unsigned long periodCombineLEDs = 2;
const unsigned long periodSpeakerPulse = 2;

/* shared variables */
unsigned char threeLEDs;
unsigned char blinkingLED;
unsigned char speakerPulse;

/* ThreeLEDsSM */
enum TL_States {TL_start, T0, T1, T2};
int ThreeLEDsSM(int state) {
	switch(state) { // transitions
		case TL_start:
			state = T0;
			break;
		case T0:
			state = T1;
			break;
		case T1:
			state = T2	;
			break;
		case T2:
			state = T0;
			break;
		default:
			state = TL_start;
			break;
	} // transitions
	switch(state) { // actions
		case TL_start:
			break;
		case T0:
			threeLEDs = 0x01;
			break;
		case T1:
			threeLEDs = 0x02;
			break;
		case T2:
			threeLEDs = 0x04;
			break;
		default:
			break;
	} // actions
	return state;
};

/* BlinkingLEDSM */
enum BL_States {BL_start, B0, B1};
int BlinkingLEDSM(int state) {
	switch(state) { // transitions
		case BL_start:
			state = B0;
			break;
		case B0:
			state = B1;
			break;
		case B1:
			state = B0;
			break;
		default:
			state = BL_start;
			break;
	} // transitions
	switch(state) { // actions
		case BL_start:
			break;
		case B0:
			blinkingLED = 0x08;
			break;
		case B1:
			blinkingLED = 0x00;
			break;
		default:
			break;
	} // actions
	return state;
};

/* SpeakerPulseSM */
enum SP_States {SP_start, off, on};
int SpeakerPulseSM(int state) {
	switch(state) { // transitions
		case SP_start:
			state = off;
			break;
		case off:
			state = (PINA & 0x04) ? on : off;
			break;
		case on:
			state = off;
			break;
		default:
			state = SP_start;
			break;
	} // transitions
	switch(state) { // actions
		case CL_start:
			break;
		case off:
			speakerPulse = 0x00;
			break;
		case on:
			speakerPulse = 0x10;
		default:
			break;
	} // actions
	return state;
};

/* CombineLEDsSM */
enum CL_States {CL_start, inf};
int CombineLEDsSM(int state) {
	switch(state) { // transitions
		case CL_start:
			state = inf;
			break;
		case inf:
			state = inf;
			break;
		default:
			state = inf;
			break;
	} // transitions
	switch(state) { // actions
		case CL_start:
			break;
		case inf:
			PORTB = blinkingLED | threeLEDs | speakerPulse;
			break;
		default:
			break;
	} // actions
	return state;
};

/* TIMER INFO FROM timer.h */
//volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1ms
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B 	= 0x0B;	// bit3 = 1: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: prescaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A 	= 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register

	TIMSK1 	= 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1 = 0;

	// TimerISR will be called every _avr_timer_cntcurr milliseconds
	_avr_timer_cntcurr = _avr_timer_M;

	//Enable global interrupts
	SREG |= 0x80;	// 0x80: 1000000
}

void TimerISR() {
	unsigned char i;
	for (i = 0; i < tasksNum; ++i) {
		if (tasks[i].elapsedTime >= tasks[i].period) {
			tasks[i].state = tasks[i].TickFct(tasks[i].state);
			tasks[i].elapsedTime = 0;
		}
		tasks[i].elapsedTime += tasksPeriodGCD;
	}
}

void TimerOff() {
	TCCR1B 	= 0x00; // bit3bit2bit1bit0=0000: timer off
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect)
{
	// CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; 			// Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { 	// results in a more efficient compare
		TimerISR(); 				// Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

int main(void) {
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	
	unsigned i = 0;
	tasks[i].state = TL_start;
	tasks[i].period = periodThreeLEDs;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &ThreeLEDsSM;
	i++;
	
	tasks[i].state = BL_start;
	tasks[i].period = periodBlinkingLED;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &BlinkingLEDSM;
	i++;

	tasks[i].state = SP_start;
	tasks[i].period = periodSpeakerPulse;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &SpeakerPulseSM;
	i++;
	
	tasks[i].state = CL_start;
	tasks[i].period = periodCombineLEDs;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &CombineLEDsSM;
	
	TimerSet(100);
	TimerOn();
	
    while (1) { }
    return 0;
}
