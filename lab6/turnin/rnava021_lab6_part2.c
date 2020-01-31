/*	Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 6  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *  Create a synchSM to blink three LEDs connected to PB0, PB1, and PB2 in sequence, 1 second each.
 *	Create a simple light game that requires pressing a button on PA0 while the middle of three LEDs on
 *	PB0, PB1, and PB2 is lit. The LEDs light for 300 ms each in sequence. When the button is pressed,
 *	the currently lit LED stays lit. Pressing the button again restarts the game.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>


enum States {start, led1, led2, led3, button} state;
	unsigned char but;

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

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

void TimerOff() {
	TCCR1B 	= 0x00; // bit3bit2bit1bit0=0000: timer off
}

void TimerISR() {
	TimerFlag = 1;
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

void Tick() {
    switch (state) { /* transitions */
    case start:
        state = but ? button : led1 ;
        break;
    case led1:
        state = but ? button : led2;
        break;
    case led2:
        state = but ? button : led3;
        break;
    case led3:
        state = but ? button : led1;
        break;
	case button:
		state = but ? led1 : button;
		break;
    default:
        state = start;
        break;
    } /* transitions */
    
    switch (state) { /* actions */
    case start:
        break;
    case led1:
        PORTB = 0x01;
        break;
    case led2:
        PORTB = 0x02;
        break;
    case led3:
        PORTB = 0x04;
        break;
	case button:
		break;
    default:
        break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PINA = 0xFF; /* Configure PORTB as input, initialized to all 1s */
    DDRB = 0xFF; PORTB = 0x00; /* Configure PORTB as output, initialized to all 0s */
	
    state = start;
    TimerSet(300);
    TimerOn();

    while (1) {
		but = (~PINA) & 0x01;
        Tick();
        while (!TimerFlag) {}
        TimerFlag = 0;
    }
    return 1;
}
