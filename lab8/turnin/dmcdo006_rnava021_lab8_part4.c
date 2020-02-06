/*	Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab #8  Exercise #4(Challenge)
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
    const unsigned short step = 0x0068; //MAX is 0x0340. Divided by 8 is equal to 0x0068
    while (1) {
        l_short = ADC;
        if(l_short < step){
            PORTB = 0x00;
        }
        else if (l_short < step*2){
            PORTB = 0x01;
	}
	else if (l_short < step*3){
            PORTB = 0x03;
	}
        else if (l_short < step*4){
            PORTB = 0x07;
        }
        else if (l_short < step*5){
            PORTB = 0x0F;
        }
        else if (l_short < step*6){
            PORTB = 0x1F;
        }
        else if (l_short < step*7){
            PORTB = 0x3F;
        }
        else if(l_short < step*8){
            PORTB = 0x7F;
        }
        else{
            PORTB = 0xFF;
        }
    }
    return 1;
}
