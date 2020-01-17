/*	Author: rnava021 Ruth Navarrete
 *  Partner(s) Name: Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 2  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *	Garage open at night-- A garage door sensor connects to PA0 (1 means door
 *	open), and a light sensor connects to PA1 (1 means light is sensed).
 *	Write a program that illuminates an LED connected to PB0 (1 means
 *	illuminate) if the garage door is open at night.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PINA = 0xFF; /* Configure port A's 8 pins as inputs */
    DDRB = 0xFF; PORTB = 0x00; /* Configure port B's 8 pins as outputs */
    unsigned char in0 = 0x00;
    unsigned char in1 = 0x00;
    unsigned char out0 = 0x00;

    /* Insert your solution below */
    while (1) {
        in0 = PINA & 0x01;
        in1 = PINA & 0x02;
        if (!in1 && in0) {
            out0 = 0x01;
        } else {
            out0 = 0x00;
        }
        PORTB = out0;
    }
    return 0;
}