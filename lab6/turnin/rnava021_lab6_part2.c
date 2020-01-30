/*	Author: rnava021
 *  Partner(s) Name: Dylan McDowell
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
#include "Debug/header/timer.h"

enum States {start, led1, led2, led3, button} state;
	unsigned char but;

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
    TimerSet(30);
    TimerOn();

    while (1) {
		but = (~PINA) & 0x01;
        Tick();
        while (!TimerFlag) {}
        TimerFlag = 0;
    }
    return 1;
}
