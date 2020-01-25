/*	Author: rnava021
 *  Partner(s) Name: Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 4 Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *	A household has a digital combination deadbolt lock system on the doorway.
 *	The system has buttons on a keypad. Button 'X' connects to PA0, 'Y' to PA1,
 *	and '#' to PA2. Pressing and releasing '#', then pressing 'Y', should unlock
 *	the door by setting PB0 to 1. Any other sequence fails to unlock. Pressing
 *	a button from inside the house (PA7) locks the door (PB0=0).
 *	For debugging purposes, give each state a number, and always write
 *	the current state to PORTC (consider using the enum state variable).
 *	Also, be sure to check that only one button is pressed at a time.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum STATES {start, init, inside_house, press_hash, unlock_door, no_action} state;

void doorLock_tick () {
    switch (state) { // transitions
        case start: // PORTC = 0x00
            state = init;
            break;
        case init: // PORTC = 0x01
            if ((PINA & 0x80) && !(PINA & 0x04)) {
                state = inside_house;
                break;
            }
            else if ((PINA & 0x04) && !(PINA & 0x80)) {
                state = press_hash;
                break;
            }
            else {
                state = init;
                break;
            }
            break;
        case inside_house: // PORTC = 0x02
            state = init;
            break;
        case press_hash: // PORTC = 0x03
            if ((PINA & 0x02) && !(PINA & 0x04) && !(PINA & 0x01)) {
                state = unlock_door;
                break;
            }
            else if ((PINA & 0x04) && !(PINA & 0x02) && !(PINA & 0x01)) {
                state = press_hash;
                break;
            }
            else {
                state = no_action;
                break;
            }
            break;
        case unlock_door: // PORTC = 0x04
            state = init;
            break;
        case no_action: // PORTC = 0x05
            state = init;
            break;
        default: // PORTC = 0xFF
            state = start;
            break;
    } // transitions
    switch (state) { // actions
        case start: // PORTC = 0x00
            PORTC = 0x00;
            PORTB = 0x00;
            break;
        case init: // PORTC = 0x01
            PORTC = 0x01;
            break;
        case inside_house: // PORTC = 0x02
            PORTC = 0x02;
            PORTB = 0x00;
            break;
        case press_hash: // PORTC = 0x03
            PORTC = 0x03;
            break;
        case unlock_door: // PORTC = 0x04
            PORTC = 0x04;
            PORTB = 0x01;
            break;
        case no_action: // PORTC = 0x05
            PORTC = 0x05;
            PORTB = 0x00;
            break;
        default: // PORTC = 0xFF
            PORTC = 0xFF;
            break;
    } // actions
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PINA = 0xFF;   // Configure port A's 8 pins as inputs
    DDRB = 0xFF; PORTB = 0x00;  // Configure port B's 8 pins as outputs
                                // Initialize output on PORTB to 0x00
    DDRC = 0xFF; PORTC = 0x00;  // Configure port C's 8 pins as outputs
                                // Initialize output on PORTC to 0x00

    /* Initialize state machine */
    state = start;

    /* Call state machine tick */
    while (1) { doorLock_tick(); }

    return 0;
}
