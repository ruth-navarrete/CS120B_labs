/*	Author: rnava021
 *  Partner(s) Name: Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 3  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *	Count the number of 1s on ports A and B and output that number on port C.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {

    DDRA = 0x00; PINA = 0xFF;
    DDRB = 0x00; PINB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    unsigned char nums_1 = 0x00;
    unsigned char inputA = 0x00;
    unsigned char inputB = 0x00;
    unsigned char i = 0x00;


    while (1) {
        nums_1 = 0;
        inputA = PINA;
        inputB = PINB;

        for (i = 0; i < 8; i++) {
            if (inputA & 0x01) {
                nums_1 = nums_1 + 1;
            }
            inputA = inputA >> 1;
        }

        for (i = 0; i < 8; i++) {
            if (inputB & 0x01) {
                nums_1 = nums_1 + 1;
            }
            inputB = inputB >> 1;
        }

        PORTC = nums_1;
    }

    return 0;
}