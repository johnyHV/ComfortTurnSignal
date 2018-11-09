/*
 * Init.c
 *
 * Created: 11/2/2018 14:00:06
 *  Author: Miroslav Pivovarsky
 */ 

#include "init.h"

void initGpioPin()
{
	// Output pin
	DDRB |= (1 << RELE_LEFT);
	PORTB |= (1 << RELE_LEFT);
	
	DDRB |= (1 << RELE_RIGHT);
	PORTB |= (1 << RELE_RIGHT);
	
	// Input pin
	DDRB &= ~(1 << INPUT_LEFT);    // switch on (INPUT_LEFT)
	PORTB |= (1 << INPUT_LEFT);    // enable pull-up resistor
	
	DDRB &= ~(1 << INPUT_RIGHT);    // switch on (INPUT_LEFT)
	PORTB |= (1 << INPUT_RIGHT);    // enable pull-up resistor
	
	PORTB &= ~(1 << RELE_LEFT);   // RELE off
	PORTB &= ~(1 << RELE_RIGHT);   // RELE off
}

void initTimer1(void)
{
	TCCR1 = 0;                  // stop the timer
	TCNT1 = 0;                  // zero the timer
	GTCCR = _BV(PSR1);          // reset the prescaler
	OCR1A = 200;					// set the compare value for A
	OCR1B = 100;					// set the compare value for B
	//OCR1C = 10;
	TIMSK = _BV(OCIE1A) | _BV(OCIE1B);        //interrupt on Compare Match A
	TIMSK |= (1 << OCIE1A);					// enable compare match interrupt
	
	//start timer, ctc mode, prescaler clk/16384
	TCCR1 = _BV(CTC1) | _BV(CS13) | _BV(CS12) | _BV(CS11) | _BV(CS10);
	//TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11); //clock prescaler 8192
	sei();
}

void initInterrupt(void)
{
	GIMSK |= (1 << PCIE);   // pin change interrupt enable
	PCMSK |= (1 << PCINT1); // pin change interrupt enabled for PCINT4
	PCMSK |= (1 << PCINT2); // pin change interrupt enabled for PCINT3
	sei();                  // enable interrupts
}