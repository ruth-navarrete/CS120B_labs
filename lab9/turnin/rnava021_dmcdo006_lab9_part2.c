/*	Author: rnava021, dmcdo006
 *  Partner(s) Name: Ruth Navarrete, Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab #9  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *	Using the ATmega1284’s PWM functionality, design a system where the notes: 
 *	C4, D, E, F, G, A, B, and C5,  from the table at the top of the lab, can 
 *	be generated on the speaker by scaling up or down the eight note scale. 
 *	Three buttons are used to control the system. One button toggles sound on/off. 
 *	The other two buttons scale up, or down, the eight note scale. Criteria:
 *		The system should scale up/down one note per button press.
 *		When scaling down, the system should not scale below a C.
 *		When scaling up, the system should not scale above a C.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void set_PWM(double frequency) {
    static double current_frequency;

    if(frequency != current_frequency) {
        if(!frequency) { TCCR3B &= 0x08; }
        else { TCCR3B |= 0x03; }

        if (frequency < 0.954) { OCR3A = 0xFFFF; }

        else if(frequency > 31250) { OCR3A = 0x0000; }

        else { OCR3A = (short)(8000000 / (128* frequency)) - 1; }

        TCNT3 = 0;
        current_frequency = frequency;
    }
}

void PWM_on() {
    TCCR3A = (1 << COM3A0);
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum States {start, init, wait, inc, inc_h, dec, dec_h, toggle, toggle_h} state;

volatile unsigned char TimerFlag = 0;
void TimerISR() { TimerFlag = 1; }

unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1ms
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}
void TimerOn() {
     // AVR timer/counter controller register TCCR1
     TCCR1B = 0x0B; // bit3 = 1: CTC mode (clear timer on compare)
     // AVR output compare register OCR1A.
     OCR1A = 125;
     TIMSK1 = 0x02;
     
     TCNT1 = 0;

     _avr_timer_cntcurr = _avr_timer_M;

     //Enable global interrupts
     SREG |= 0x80;
}

void TimerOff() {
    TCCR1B = 0x00; // bit3bit2bit1bit0=0000: timer off
}

ISR(TIMER1_COMPA_vect)
{
    //CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
    _avr_timer_cntcurr--; 		// Count down to 0 rather than up to TOP
    if (_avr_timer_cntcurr == 0) {      // results in a more efficient compare
        TimerISR(); 			// Call the ISR that the user uses
        _avr_timer_cntcurr = _avr_timer_M;
    }
}
//Global Variables
double freq; //Holds the frequency that the speaker will be set at.
double freqs[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char en; // indicates whether or not the speaker is on.
unsigned char i; //Holds the index position of our current position. Goes no lower than 0,
                 // no higher than 7.

unsigned char a0; // bit 0 on port A
unsigned char a1; // bit 1 on port A
unsigned char a2; // bit 2 on port A

void get_input(){
    a0 = (~PINA & 0x01);
    a1 = (~PINA & 0x02);
    a2 = (~PINA & 0x04);
}

void Tick() {
    get_input();
    switch(state) { //Transitions
    case start:
        state = init;
        break;
    case init:
        state = wait;
        break;
    case wait:
        if(a2){
            state = toggle;
        }
        else if(!a2 && !a1 && a0){
            state = inc;
        }
        else if(!a2 && a1 && !a0){
            state = dec;
        }
        else if(!a2 && a1 && a0){
            state = wait;
        }
        else{
            state = wait;
        }
        break;
    case inc:
        state = inc_h;
        break;
    case inc_h:
        state = (a2 || a1 || a0) ? inc_h : wait;
        break;
    case dec:
        state = dec_h;
        break;
    case dec_h:
        state = (a2 || a1 || a0) ? dec_h : wait;
        break;
    case toggle:
        state = toggle_h;
        break;
    case toggle_h:
        state = (a2 || a1 || a0) ? toggle_h : wait;
        break;
    default:
        state = start;
        break;
    }

    switch(state) { //Actions
    case start:
        break;
    case init:
        freq = freqs[0];
        break;
    case wait:
        break;
    case inc:
        if (i < 7){
            i++;
        }
        freq = freqs[i];
        break;
    case inc_h:
        break;
    case dec:
        if(i > 0){
            i--;
        }
		freq = freqs[i];
        break;
    case dec_h:
        break;
    case toggle:
        if(en){
            en = 0;
            PWM_off();
        }
        else{
            en = 1;
            PWM_on();
        }
        break;
    case toggle_h:
        break;
    default:
        break;
    }

    set_PWM(freq);
}

int main(void) {
    DDRA = 0x00; PINA = 0xFF; // Initialize port A's 8 pins to input
    DDRB = 0xFF; PORTB = 0x00; // Initialize port B's 8 pins to output
                               // Set port B's pins to 0
    PWM_on();
    TimerSet(100);
    TimerOn();
    freq = 0;
    en = 1;
    while (1) {
         Tick();
         while(!TimerFlag){}
         TimerFlag = 0;
    }
    return 1;
}