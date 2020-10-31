/*
 * Conf.h
 *
 * Created: 15. 10. 2020 8:21:08
 *  @author Miroslav Pivovarsky (mpivovarsky)
 *  @version 0.1
 *  @bug No know bugs.
 *
 */ 

#ifndef CONF_H_
#define CONF_H_

#include <avr/io.h>

#define SOFTWARE_VERSION		"1.4.1"	///< Software version
#define HARDWARE_VERSION		12		///< hardware version 1.1 or 1.2

#define F_CPU 8000000					///< 8.0Mhz/8 = 1.0Mhz

#if (HARDWARE_VERSION == 12)
#define INPUT_LEFT				PB2		///< LEFT input
#define INPUT_RIGHT				PB1		///< RIGHT input
#define INPUT_SET_BUTTON		PB0		///< configuration button input
#define RELE_LEFT				PB4		///< LEFT rele
#define RELE_RIGHT				PB3		///< RIGHT rele
#endif

#if (HARDWARE_VERSION == 11)
#define INPUT_LEFT				PB4		///< LEFT input
#define INPUT_RIGHT				PB3		///< RIGHT input
#define INPUT_SET_BUTTON		PB0		///< configuration button input
#define RELE_LEFT				PB2		///< LEFT rele
#define RELE_RIGHT				PB1		///< RIGHT rele
#endif

#define EEPROM_ENABLE			0		///< Enable/disable EEPROM memmory
#define EEPROM_TIME_FLASHING	0x00	///< EEPROM address for store uint16 value for time BULB ON and OFF
#define BLINK_INTERVAL			3		///< triple flash interval
#define REFRESH_TIME			5		///< Refres time for super loop
#define SAFETY_DELAY			500		///< Safety timer
#define TIME_ON_OFF_LENGTH		400		///< timer for length bulb on and off
#define TIMEOUT_ENABLE_BULB		300		///< timeout for enable turn ON bulb
#define MIN_TIME_FOR_EN_TRIPP	80		///< Minimum time for enable trippling

#define TRUE 1							///< True value
#define FALSE 0							///< False value
#define BULB_ON TRUE					///< Bulb on value
#define BULB_OFF FALSE					///< Bulb off value

#endif /* CONF_H_ */