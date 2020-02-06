/*	Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab #8 Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init() {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF; //Configure port A's 8 pins as inputs
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00; //Configure port B and D's pins to outputs
                               //Initialize both to zero
    ADC_init();
    unsigned short l_short;
    unsigned char lu_char;
    unsigned char ll_char;
    while (1) {
        l_short = ADC;
        ll_char = (char)l_short;
        lu_char = (char)(l_short >> 8);
        PORTB = ll_char;
        PORTD = lu_char;
    }
    return 1;
}
