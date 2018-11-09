/*
 * Variable.c
 *
 * Created: 11/2/2018 14:00:38
 *  Author: Miroslav Pivovarsky
 */ 

#include "Variable.h"

struct DirectionalLight DirectionalLightLeft= {0, 0, BULB_OFF, FALSE, 0, 0, RELE_LEFT, INPUT_LEFT};
struct DirectionalLight DirectionalLightRight = {0, 0, BULB_OFF, FALSE, 0, 0, RELE_RIGHT, INPUT_RIGHT};

uint16_t TimeForEnableAutoFlashing = 200/REFRESH_TIME;
uint16_t TimeForFlashingOn = 500/REFRESH_TIME;
uint16_t TimeForFlashingOff = 500/REFRESH_TIME;

