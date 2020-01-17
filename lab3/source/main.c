/*	Author: rnava021
 *  Partner(s) Name: Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 3  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *	A car has a fuel-level sensor that sets PA3..PA0 to a value between
 *	0 (empty) and 15 (full). PA4 is 1 if a key is in the ignition,
 *	PA5 is one if a driver is seated, and PA6 is 1 if the driver's
 *	seatbelt is fastened. A series of LEDs connected to PC5..PC0
 *	should light to graphically indicate the fuel level. If the fuel
 *	level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light.
 *	Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..PC1.
 *	13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon,
 *	which should light if the level is 4 or less. PC7 should light a
 *	"Fasten seatbelt" icon if a key is in the ignition, the driver
 *	is seated, but the belt is not fastened.
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

        if ((PINA & 0x0F) < 5) {
            /* All fuels 4 and below have PC6 lit */
            outputC = 0x40;

            /* if PINA nibble0 == 0*/
            if ((PINA & 0x0F) == 0) {
            }
            /* if PINA nibble0 == 1 || PINA nibble0 == 2 */
            else if ((PINA & 0x0F) < 3) {
                outputC = outputC | 0x20;
            }
            /* if PINA nibble0 == 3 || PINA nibble0 == 4 */
            else if ((PINA & 0x0F) < 5) {
                outputC = outputC | 0x30;
            }
        }
        /*if PINA nibble0 == 5 || PINA nibble0 == 6 */
        else if ((PINA & 0x0F) < 7) {
            outputC = 0x38;
        }
        /* if PINA nibble0 == 7 || PINA nibble0 == 8 || PINA nibble0 == 9 */
        else if ((PINA & 0x0F) < 10) {
            outputC = 0x3C;
        }
        /* if PINA nibble0 == 10 || PINA nibble0 == 11 || PINA nibble0 == 12 */
        else if ((PINA & 0x0F) < 13) {
            outputC = 0x3E;
        }
        /* if PINA nibble0 == 13 || PINA nibble0 == 14 || PINA nibble0 == 15 */
        else if ((PINA & 0x0F) < 16) {
            outputC = 0x3F;
        }

        /* if ~PA6 & PA5 & PA4 */
        if ( ((PINA & 0x70) ) == 0x30) {
            outputC = outputC | 0x80;
        }
        
        PORTC = outputC;
    }

    return 0;
}