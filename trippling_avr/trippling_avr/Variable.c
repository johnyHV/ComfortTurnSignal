/** @file Variable.c
 *  @brief A System function
 *
 *  Global variable
 *
 *  @date 11/2/2018 14:00:51
 *  @author Miroslav Pivovarsky (mpivovarsky)
 *  @version 0.1
 *  @bug No know bugs.
 */

#include "Variable.h"

struct DirectionalLight DirectionalLightLeft= {0, 0, BULB_OFF, FALSE, 0, 0, RELE_LEFT, INPUT_LEFT};
struct DirectionalLight DirectionalLightRight = {0, 0, BULB_OFF, FALSE, 0, 0, RELE_RIGHT, INPUT_RIGHT};

uint16_t TimeForEnableAutoFlashing = TIMEOUT_ENABLE_BULB/REFRESH_TIME; 
uint16_t TimeMinimalForEnableAutoFlashing = MIN_TIME_FOR_EN_TRIPP/REFRESH_TIME;
uint16_t TimeForFlashing = TIME_ON_OFF_LENGTH/REFRESH_TIME;

void ClearStruct () {
	DirectionalLightLeft.TimerCounterFlashing = 0;
	DirectionalLightLeft.StatusFlashing = BULB_OFF;
	DirectionalLightLeft.EnableFlashing = FALSE;
	DirectionalLightLeft.CounterFlashing = 0;
	DirectionalLightLeft.StartTimerCounterUp = 0;
	DirectionalLightLeft.TimeCountUp = 0;
	
	DirectionalLightRight.TimerCounterFlashing = 0;
	DirectionalLightRight.StatusFlashing = BULB_OFF;
	DirectionalLightRight.EnableFlashing = FALSE;
	DirectionalLightRight.CounterFlashing = 0;
	DirectionalLightRight.StartTimerCounterUp = 0;
	DirectionalLightRight.TimeCountUp = 0;
}