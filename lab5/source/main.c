/*	Author: rnava021
 *  Partner(s) Name: Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 3  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *	A car has a fuel-level sensor that sets PA3..PA0 to a value between
 *	0 (empty) and 15 (full). A series of LEDs connected to PC5..PC0 should
 *	light to graphically indicate the fuel level. If the fuel level is
 *	1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light.
 *	Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..PC1.
 *	13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon,
 *	which should light if the level is 4 or less.
 *  Use buttons on PA3..PA0 and mimic the fuel-level sensor with presses.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {

    DDRB = 0xFF; PORTB = 0x00; /* Configure PORTB as output, initialize to 0s */
    
    while (1) {
        PORTB = 0X0F;
    }
    return 0;
}
