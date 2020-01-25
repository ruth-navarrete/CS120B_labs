/*	Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 5 Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *	Buttons are connected to PA0 and PA1. Output for PORTC is initially 7. 
 *	Pressing PA0 increments PORTC once (stopping at 9). 
 *	Pressing PA1 decrements PORTC once (stopping at 0). If both buttons 
 *	are depressed (even if not initially simultaneously), PORTC resets to 0.
 *  If a reset occurs, both buttons should be fully released before additional
 *  increments or decrements are allowed to happen. Use LEDs (and resistors)
 *  on PORTC. Use a state machine (not synchronous) captured in C. 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum STATES {start, init, wait, inc, i_hold, dec, d_hold, reset} state;
unsigned char tempC;

void button_tick () {
    switch (state) { // transitions
        case start:
            state = init;
            break;
        case init:
            state = wait;
            break;
        case wait:
            if((PINA & 0x01) && (PINA & 0x02)){
		state = reset;
	    }
	    else if(PINA & 0x01){
		state = inc;
	    }
	    else if(PINA & 0x02){
		state = dec;
	    }
	    else if(!((PINA & 0x01) || (PINA & 0x02))) {
		state = wait;
	    }
            break;
        case inc:
            state = i_hold;
            break;
        case i_hold:
            if(!((PINA & 0x01) || (PINA & 0x02))){
		state = wait;
	    }
	    else if((PINA & 0x01) && !(PINA & 0x02)){
                state = i_hold;
	    }
            else if(PINA & 0x02){
                state = reset;
            }
            else{
                state = i_hold;
	    }
            break;
	case dec:
            state = d_hold;
	    break;
	case d_hold:
            if(!((PINA & 0x01) || (PINA & 0x02))){
                state = wait;
            }
            else if((PINA & 0x02) && !(PINA & 0x01)){
                state = d_hold;
            }
            else if(PINA & 0x01){
                state = reset;
            }
            else{
                state = d_hold;
            }
	    break;
	case reset:
            state = ((PINA & 0x01) || (PINA & 0x02)) ? reset : wait;
	    break;
        default:
            state = start;
            break;
    } // transitions
    switch (state) { // actions
        case start: //Does nothing
            break;
        case init: //Initializes output to 0x07
            tempC = 0x07;
            break;
        case wait: //Does nothing
            break;
        case inc: //Increments if cap hasn't been reached
            if(tempC < 9){
                tempC = tempC + 1;
            }
            break;
        case i_hold: //Does nothing
            break;
        case dec: //Increments if cap hasn't been reached
            if(tempC > 0){
                tempC = tempC - 1;
            }
            break;
        case d_hold: //Does nothing
            break;
        case reset: //Resets to 0
            tempC = 0;
            break;
        default:
            break;

    } // actions

    PORTC = tempC; //Sets output on port C equivalent to result
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PINA = 0xFF;  // Configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00;  // Configure port C's 8 pins as outputs
                                // Initialize output on PORTC to 0x00

    /* Initialize state machine */
    state = start;
    /* Initialize tempC value */
    tempC = 0x00;

    /* Call state machine tick */
    while (1) { button_tick(); }

    return 0;
}
