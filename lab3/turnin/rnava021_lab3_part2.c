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
    unsigned char outputC = 0x00;

    while (1) {
        outputC = 0x00;

        if (PINA < 5) {
            /* All fuels 4 and below have PC6 lit */
            outputC = 0x40;

            /* if PINA == 0*/
            if (PINA == 0) {
            }
            /* if PINA == 1 || PINA == 2 */
            else if (PINA < 3) {
                outputC = outputC | 0x20;
            }
            /* if PINA == 3 || PINA == 4 */
            else {
                outputC = outputC | 0x30;
            }
        }
        /*if PINA == 5 || PINA == 6 */
        else if (PINA < 7) {
            outputC = 0x38;
        }
        /* if PINA == 7 || PINA == 8 || PINA == 9 */
        else if (PINA < 10) {
            outputC = 0x3C;
        }
        /* if PINA == 10 || PINA == 11 || PINA == 12 */
        else if (PINA < 13) {
            outputC = 0x3E;
        }
        /* if PINA == 13 || PINA == 14 || PINA == 15 */
        else if (PINA < 16) {
            outputC = 0x3F;
        }
        else {
            outputC = 0x00;
        }
        
        PORTC = outputC;
    }

    return 0;
}