/*Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 9 Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *	When a button is pressed, the tone mapped to it is generated on the speaker.
 *	Criteria:
 *	Use the tones C4, D4, and E4 from the table in the introduction section.
 *	When a button is pressed and held, the tone mapped to it is generated on the speaker.
 *	When more than one button is pressed simultaneously, the speaker remains silent.
 *	When no buttons are pressed, the speaker remains silent.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

// 0.954 Hz is lowest frequency possible with this function,
// based on setting in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } // stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counter
			
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is the smallest frequency that will not result in overflow	
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		
		// prevents OCR3A from underflowing, using prescaler 64
		// 31250 is the largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else {OCR3A = (short)(8000000 / (128* frequency)) - 1; }
			
		TCNT3 = 0; // resets ounter
		current_frequency = frequency; // update current frequency
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
		// COM3A0: toggle PB3 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
		// WGM32: when counter (TCNT3) matches OCR3A, reset counter
		// CS31 & CS30: set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}


int main(void) {
    DDRB = 0x40; PORTB = 0x00;
	DDRA = 0x00; PINA = 0xFF;
	unsigned char input_A = 0x00;
	PWM_on();
	
	while (1) {
		input_A = ~PINA & 0x07;
		
		if ((input_A & 0x01) && !(input_A & 0x02) && !(input_A & 0x04)) {
			// output C4
			set_PWM(261.63);
		}
		else if (!(input_A & 0x01) && (input_A & 0x02) && !(input_A & 0x04)) {
			// output D4
			set_PWM(293.66);
		}
		else if (!(input_A & 0x01) && !(input_A & 0x02) && (input_A & 0x04)) {
			// output E4
			set_PWM(329.23);
		}
		else {
			// no output
			set_PWM(0);
		}
	}
}