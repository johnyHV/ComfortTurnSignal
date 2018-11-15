/** @file Variable.h
 *  @brief A System function
 *
 *  Global variable
 *
 *  @date 11/2/2018 14:00:51
 *  @author Miroslav Pivovarsky (mpivovarsky)
 *  @version 0.1
 *  @bug No know bugs.
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <avr/io.h>

#define F_CPU 8000000				///< 8.0Mhz/8 = 1.0Mhz

#define INPUT_LEFT PB2				///< LEFT input
#define INPUT_RIGHT PB1				///< RIGHT input
#define INPUT_SET_BUTTON PB0		///< configuration button input
#define RELE_LEFT PB3				///< LEFT rele
#define RELE_RIGHT PB4				///< RIGHT rele

#define EEPROM_TIME_FLASHING 0x00	///< EEPROM address for store uint16 value for time BULB ON and OFF

#define BLINK_INTERVAL 3			///< triple flash

#define REFRESH_TIME 5				///< Refres time for super loop

extern uint16_t TimeForEnableAutoFlashing;	///< Cycle time for enable trippling
extern uint16_t TimeForFlashing;			///< Cycle for bulb flashing

#define TRUE 1						///< True value
#define FALSE 0						///< False value
#define BULB_ON TRUE				///< Bulb on value
#define BULB_OFF FALSE				///< Bulb off value

struct DirectionalLight {
	uint8_t CounterFlashing;		///< Bulb flash counter
	uint16_t TimerCounterFlashing;  ///< Delay time for enable/disable bulb
	uint8_t StatusFlashing;			///< On or Off bulb
	
	uint8_t EnableFlashing;			///< Automation flashing is enable/disable
	uint16_t TimeCountUp;			///< Time check, if is enable automation flashing, or not
	uint8_t StartTimerCounterUp;	///< Counter for start timer
	
	uint8_t Led;					///< LED pin
	uint8_t Button;					///< Input pin
};

extern struct DirectionalLight DirectionalLightLeft;	///< Left direction bulb
extern struct DirectionalLight DirectionalLightRight;	///< Right direction bulb

#endif /* VARIABLE_H_ */