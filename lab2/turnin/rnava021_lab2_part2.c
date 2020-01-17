/*	Author: rnava021 Ruth Navarrete
 *  Partner(s) Name: Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 2  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *  Port A's pins 3 to 0, each connect to a parking space sensor, 1 meaning
 *  a car is parked in the space, of a four-space parking lot. Write a program
 *  that outputs in binary on port C the number of available spaces.
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
    DDRC = 0xFF; PORTC = 0x00;
    unsigned char in0 = 0x00;
    unsigned char in1 = 0x00;
    unsigned char in2 = 0x00;
    unsigned char in3 = 0x00;
    unsigned char cntavail = 0x00;

    while (1) {
        in0 = PINA & 0x01;
        in1 = PINA & 0x02;
        in2 = PINA & 0x04;
        in3 = PINA & 0x08;
        cntavail = 0;

        if (!in0) {
            cntavail = cntavail + 1;
        }
        if (!in1) {
            cntavail = cntavail + 1;
        }
        if (!in2) {
            cntavail = cntavail + 1;
        }
        if (!in3) {
            cntavail = cntavail + 1;
        }
        if (in3 && in2 && in1 && in0) {
            cntavail = 0x00;
        }

        PORTC = cntavail;
    }
    return 0;
}