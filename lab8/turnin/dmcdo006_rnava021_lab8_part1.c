/*	Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 8 Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *	Buttons are connected to PA0 and PA1. Output for PORTC is initially 7. 
 *	Pressing PA0 increments PORTC once (stopping at 9). 
 *	Pressing PA1 decrements PORTC once (stopping at 0). If both buttons 
 *	are depressed (even if not initially simultaneously), PORTC resets to 0. 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	/* ADEN:  setting this bit enables analog-to-digital conversion
	 * ADSC:  setting this bit starts the first conversion
	 * ADATE: setting this bit enables auto-triggering. Since we are
	 *        in Free Running Mode, a new conversion will trigger whenever
	 *        the previous conversion completes
	 */
}

int main(void) {
	/* Insert DDR and PORT initializations */
	DDRA = 0x00; PINA = 0xFF;  /* Configure PORTA's 8 pins as inputs, initialize to 0s */
	DDRB = 0xFF; PORTB = 0x00;  /* Configure PORTB's 8 pins as outputs, initialize to 0s */
	DDRD = 0xFF; PORTD = 0x00;  /* Configure PORTD's 8 pins as outputs, initialize to 0s */
	
	ADC_init();
	unsigned short in_A;
	unsigned char out_lower;
	unsigned char out_upper;
	
	
	while (1) {
		in_A = ADC; /* in_A = value of ADC register */
		out_lower = (char)in_A; /* out_lower = lower two bytes of ADC register */
		out_upper = (char)(in_A >> 8); /* out_upper = upper two bytes of ADC register */
		PORTB = out_lower;
		PORTD = out_upper;
	}
	return 0;
}
