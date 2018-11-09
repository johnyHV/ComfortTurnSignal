/*
 * Variable.h
 *
 * Created: 11/2/2018 14:00:51
 *  Author: Miroslav Pivovarsky
 */ 


#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <avr/io.h>

#define F_CPU 8000000 //8.0Mhz/8 = 1.0Mhz

#define INPUT_LEFT PB2
#define INPUT_RIGHT PB1
#define RELE_LEFT PB3
#define RELE_RIGHT PB4

#define BLINK_INTERVAL 3		// triple flash

#define REFRESH_TIME 10

extern uint16_t TimeForEnableAutoFlashing;
extern uint16_t TimeForFlashingOn;
extern uint16_t TimeForFlashingOff;

#define TRUE 1
#define FALSE 0
#define BULB_ON TRUE
#define BULB_OFF FALSE

struct DirectionalLight {
	uint8_t CounterFlashing;		// Bulb flash counter
	uint16_t TimerCounterFlashing;  // Delay time for enable/disable bulb
	uint8_t StatusFlashing;			// On or Off bulb
	
	uint8_t EnableFlashing;			// Automation flashing is enable/disable
	uint16_t TimeCountUp;			// Time check, if is enable automation flashing, or not
	uint8_t StartTimerCounterUp;
	
	uint8_t Led;
	uint8_t Button;
};

extern struct DirectionalLight DirectionalLightLeft;
extern struct DirectionalLight DirectionalLightRight;

#endif /* VARIABLE_H_ */