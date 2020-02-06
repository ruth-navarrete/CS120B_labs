/*	Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
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
    DDRB = 0xFF; PORTB = 0x00; //Configure port B's pins to outputs
                               //Initialize to zero
    ADC_init();
    unsigned short l_short;
    const unsigned short max = 0x0340;
    while (1) {
        l_short = ADC;
        if(l_short >= max/2){
            PORTB = 0x01;
        }
        else{
            PORTB = 0x00;
	}
    }
    return 1;
}
