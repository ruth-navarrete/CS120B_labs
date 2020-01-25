/*	Author: rnava021
 *  Partner(s) Name: Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 4 Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *	PB0 and PB1 each connect to an LED, and PB0's LED is initially on.
 *	Pressing a button connected to PA0 turns off PB0's LED and turns
 *	on PB1's LED, staying that way after button release. Pressing the
 *	button again turns off PB1's LED and turns on PB0's LED.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum STATES {start, init, button_pressed, wait_button, between_presses} state;

void button_tick () {
    switch (state) { // transitions
        case start:
            state = init;
            break;
        case init:
            state = (PINA & 0x01) ? button_pressed : init;
            break;
        case button_pressed:
            state = (PINA & 0x01) ? wait_button : between_presses;
            break;
        case wait_button:
            state = (PINA & 0x01) ? button_pressed : between_presses;
            break;
        case between_presses:
            state = (PINA & 0x01) ? button_pressed : between_presses;
            break;
        default:
            state = start;
            break;
    } // transitions
    switch (state) { // actions
        case start:
            break;
        case init:
            PORTB = 0x01;
            break;
        case button_pressed:
            PORTB = ~(PORTB | 0xFC);
            break;
        case wait_button:
            break;
        case between_presses:
            break;
       default:
            break;
    } // actions
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PINA = 0xFF;  // Configure port A's 8 pins as inputs
    DDRB = 0xFF; PORTB = 0x00;  // Configure port B's 8 pins as outputs
                                // Initialize output on PORTB to 0x00

    /* Initialize state machine */
    state = start;

    /* Call state machine tick */
    while (1) { button_tick(); }

    return 0;
}
