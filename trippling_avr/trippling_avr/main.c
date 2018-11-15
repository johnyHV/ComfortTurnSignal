/** @file trippling_avr.c
 *  @brief A System function
 *
 *  Main function
 * 
 *  https://embeddedthoughts.com/2016/06/06/attiny85-introduction-to-pin-change-and-timer-interrupts/
 *
 *  @date 10/31/2018 13:28:07
 *  @author Miroslav Pivovarsky (mpivovarsky)
 *  @version 0.1
 *  @bug No know bugs.
 */

#define F_CPU 8000000 //8.0Mhz/8 = 1.0Mhz

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#include "Init.h"
#include "Task.h"
#include "Variable.h"

int main(void)
{
	MCUSR = 0;
	wdt_disable();
	
	initGpioPin();
	//initTimer1();
	//initInterrupt();
	//WriteTime(TimeForFlashing); // For manual first init Time 
	ReadTime();
	CheckSetButton();
	
	wdt_reset();
	wdt_enable(WDTO_1S);
	
	while(1)
	{
		CheckButton();
		Flashing();
		_delay_ms(REFRESH_TIME);
		wdt_reset();
	}
}

/** @brief ISR
 *
 *  Callback Function for Timer1 Comparator A
 *
 *  @param TIMER1_COMPA_vect
 *  @return void
*/
ISR(TIMER1_COMPA_vect)
{
	//PINB |= _BV(PINB4);         //flash the LED by toggling PB4
	TCNT1 = 0;
}

/** @brief ISR
 *
 *  Callback Function for Timer1 Comparator B
 *
 *  @param TIMER1_COMPB_vect
 *  @return void
*/
ISR(TIMER1_COMPB_vect)
{
	//PINB |= _BV(PINB3);
}

/** @brief ISR
 *
 *  Callback Function for pin interrupt
 *
 *  @param PCINT0_vect
 *  @return void
*/
ISR(PCINT0_vect)
{
	/* GPIO interrupt */
}
