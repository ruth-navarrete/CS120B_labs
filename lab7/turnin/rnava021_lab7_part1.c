/*	Author: rnava021
 *  Partner(s) Name: Dylan McDowell
 *	Lab Section: 24
 *	Assignment: Lab 7 Exercise 1
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

void LCD_init();
void LCD_ClearScreen(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_Cursor (unsigned char column);
void LCD_DisplayString(unsigned char column ,const unsigned char *string);
void delay_ms(int miliSec);

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))

/*-------------------------------------------------------------------------*/

#define DATA_BUS PORTC		// port connected to pins 7-14 of LCD display
#define CONTROL_BUS PORTD	// port connected to pins 4 and 6 of LCD disp.
#define RS 6			// pin number of uC connected to pin 4 of LCD disp.
#define E 7			// pin number of uC connected to pin 6 of LCD disp.

/*-------------------------------------------------------------------------*/

void LCD_ClearScreen(void) {
	LCD_WriteCommand(0x01);
}

void LCD_init(void) {

	//wait for 100 ms.
	delay_ms(100);
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x0f);
	LCD_WriteCommand(0x01);
	delay_ms(10);
}

void LCD_WriteCommand (unsigned char Command) {
	CLR_BIT(CONTROL_BUS,RS);
	DATA_BUS = Command;
	SET_BIT(CONTROL_BUS,E);
	asm("nop");
	CLR_BIT(CONTROL_BUS,E);
	delay_ms(2); // ClearScreen requires 1.52ms to execute
}

void LCD_WriteData(unsigned char Data) {
	SET_BIT(CONTROL_BUS,RS);
	DATA_BUS = Data;
	SET_BIT(CONTROL_BUS,E);
	asm("nop");
	CLR_BIT(CONTROL_BUS,E);
	delay_ms(1);
}

void LCD_DisplayString( unsigned char column, const unsigned char* string) {
	LCD_ClearScreen();
	unsigned char c = column;
	while(*string) {
		LCD_Cursor(c++);
		LCD_WriteData(*string++);
	}
}

void LCD_Cursor(unsigned char column) {
	if ( column < 17 ) { // 16x1 LCD: column < 9
		// 16x2 LCD: column < 17
		LCD_WriteCommand(0x80 + column - 1);
		} else {
		LCD_WriteCommand(0xB8 + column - 9);	// 16x1 LCD: column - 1
		// 16x2 LCD: column - 9
	}
}

void delay_ms(int miliSec) //for 8 Mhz crystal

{
	int i,j;
	for(i=0;i<miliSec;i++)
	for(j=0;j<775;j++)
	{
		asm("nop");
	}
}

enum STATES {start, init, inc_button, dec_button, do_nothing, reset} state;
unsigned char led;

volatile unsigned char TimerFlag = 0;	/* TimerISR() sets this to 1. C programmer should clear to 0. */

/* Internal variables for mapping AVR's ISR to our cleaner TimerISR model. */

unsigned long _avr_timer_M = 1; /* Start count from here, down to 0. Default 1 ms. */
unsigned long _avr_timer_cntcurr = 0; /* Current internal count of 1 ms ticks */

void TimerOn() {
	/* AVR timer/counter controller register TCCR1 */
	TCCR1B = 0x0B;	/* bit1 = 0: CTC mode (clear timer on compare)
					 * bit2bit1bit0=011: pre-scale /64
					 * 00001011: 0x0B
					 * So, 8 MHz lock or 8,000,000 /64 = 125,000 ticks/s
					 * Thus TCNT1 register will count at 125,000 ticks/s
					 */
	
	/* AVR output compare register OCR1A */
	OCR1A = 125;	/* Timer interrupt will be generated when TCNT1 == OCR1A
					 * We want a 1 ms tick.. 0.001 s * 125,000 ticks/s = 125
					 * So when TCNT1 register equals 125
					 * 1 ms has passed. Thus, we compare to 125
					 */
	
	/* AVR timer interrupt mask register */
	TIMSK1 = 0x02; /* bit1: OCIE1A -- enables compare math interrupt */
	
	/* Initialize avr counter */
	TCNT1 = 0;
	
	/* Enable global interrupts */
	SREG |= 0x80; /* 0x80: 1000 0000 */
}

void TimerOff() {
	TCCR1B = 0x00; /* bit3bit1bit0-000: timer off */
}

void TimerISR() {
	TimerFlag = 1;
}

/* In our approach, C programmer does not touch this ISR but rather TimerISR() */
ISR(TIMER1_COMPA_vect) {
	/* CPU automaticall calls when TCNT1 == OCR1 (every 1 ms per TimerOne Settings) */
	_avr_timer_cntcurr--; /* Count down to 0 rather than up to TOP */
	if (_avr_timer_cntcurr == 0) { /* results in a more efficient compare */
		TimerISR(); /* Call the ISR that the user uses */
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

/* Set TimerISR() to tick every M ns */
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void determine_button(unsigned char b_inc, unsigned char b_dec) {
	if (b_inc && b_dec) {
		state = reset;
	}
	else if (b_inc && (!b_dec)) {
		state = inc_button;
	}
	else if ((!b_inc) && b_dec) {
		state = dec_button;
	}
	else {
		state = do_nothing;
	}
}

void update_led(unsigned char led) {
	LCD_ClearScreen();
	LCD_Cursor(1);
	LCD_WriteData( led + '0' );
}

void LED_tick () {
	unsigned char b_inc = ~(PINA) & 0x01;
	unsigned char b_dec = ~(PINA) & 0x02;
	
    switch (state) { // transitions
        case start:
            state = init;
            break;
        case init:
			determine_button(b_inc, b_dec);
			break;
        case inc_button:
			determine_button(b_inc, b_dec);
			break;
		case dec_button:
			determine_button(b_inc, b_dec);
			break;
		case do_nothing:
			determine_button(b_inc, b_dec);
			break;
		case reset:
			determine_button(b_inc, b_dec);
			break;
        default:
            state = start;
            break;
    } // transitions
	
    switch (state) { // actions
        case start:
			break;
        case init:
			led = 7;
			update_led(led);
			break;
        case inc_button:
			if (led < 9) { led++; }
			update_led(led);
			break;
        case dec_button:
			if (led > 0) { led--; }
			update_led(led);
			break;
		case do_nothing:
			update_led(led);
			break;
		case reset:
			led = 0;
			update_led(led);
			break;
        default:
			break;
    } // actions
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PINA = 0xFF;  // Configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00;  // LCD data lines
	DDRD = 0xFF; PORTD = 0x00;  // LCD control lines

    /* Initialize state machine */
    state = start;
    
	/* Initialize led value */
    led = 0x00;
	
	/* Initialize clock */
	TimerSet(1000);
	TimerOn();
	
	/* Initialize LCD display */
	LCD_init();

    /* Call state machine tick */
    while (1) {
		LED_tick();
		while (!TimerFlag) {}
		TimerFlag = 0;
	}

    return 0;
}
