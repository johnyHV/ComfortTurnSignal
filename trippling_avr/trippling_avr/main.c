/*
* trippling_avr.c
*
* Created: 10/31/2018 13:28:07
* Author : Miroslav Pivovarsky
*
* https://embeddedthoughts.com/2016/06/06/attiny85-introduction-to-pin-change-and-timer-interrupts/
*
*/

#define F_CPU 8000000 //8.0Mhz/8 = 1.0Mhz

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#include "Variable.h"
#include "Init.h"
#include "Task.h"

int main(void)
{
	MCUSR = 0;
	wdt_disable();
	
	initGpioPin();
	initTimer1();
	initInterrupt();
	
	wdt_reset();
	//wdt_enable(WDTO_1S);
	
	while(1)
	{
		CheckButton();
		Flashing();
		_delay_ms(REFRESH_TIME);
		wdt_reset();
	}
}



ISR(TIMER1_COMPA_vect)
{
	//PINB |= _BV(PINB4);         //flash the LED by toggling PB4
	TCNT1 = 0;
}

ISR(TIMER1_COMPB_vect)
{
	//PINB |= _BV(PINB3);
}

ISR(PCINT0_vect)
{
	/* GPIO interrupt */
}
