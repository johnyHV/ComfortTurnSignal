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
#include "Conf.h"

extern uint16_t TimeForEnableAutoFlashing;	///< Cycle time for enable trippling
uint16_t TimeMinimalForEnableAutoFlashing;	///< Minimum cycle time for enable trippling
extern uint16_t TimeForFlashing;			///< Cycle for bulb flashing

struct DirectionalLight {
	uint8_t CounterFlashing;				///< Bulb flash counter
	uint16_t TimerCounterFlashing;			///< Delay time for enable/disable bulb
	uint8_t StatusFlashing;					///< On or Off bulb
	
	uint8_t EnableFlashing;					///< Automation flashing is enable/disable
	uint16_t TimeCountUp;					///< Time check, if is enable automation flashing, or not
	uint8_t StartTimerCounterUp;			///< Counter for start timer
	
	uint8_t Led;							///< LED pin
	uint8_t Button;							///< Input pin
};

extern struct DirectionalLight DirectionalLightLeft;	///< Left direction bulb
extern struct DirectionalLight DirectionalLightRight;	///< Right direction bulb

void ClearStruct ();

#endif /* VARIABLE_H_ */