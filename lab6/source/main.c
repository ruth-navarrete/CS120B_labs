/*	Author: rnava021
 *  Partner(s) Name: Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 6  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *  Create a synchSM to blink three LEDs connected to PB0, PB1, and PB2 in sequence, 1 second each.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, led1, led2, led3} state;

volatile unsigned char TimerFlag = 0;
void TimerISR() { TimerFlag = 1; }
void Tick() {
    switch (state) { /* transitions */
    case start:
        state = led1;
        break;
    case led1:
        state = led2;
        break;
    case led2:
        state = led3;
        break;
    case led3:
        state = led1;
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
    default:
        break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00; /* Configure PORTB as output, initialized to all 0s*/
    state = start;
    TimerSet(1000);
    TimerOn();

    while (1) {
        Tick();
        while (!TimerFlag) {}
        TimerFlag = 0;
    }
    return 1;
}
