/*
 * Task.h
 *
 * Created: 11/2/2018 16:59:18
 *  Author: Miroslav Pivovarsky
 */ 


#ifndef TASK_H_
#define TASK_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "Variable.h"

void Flashing(void);
void FlashingLed(struct DirectionalLight *);
void CheckButton(void);
void CheckInput(struct DirectionalLight *);
uint8_t SafetyCheck(void);
void MeasureTime(void);

#endif /* TASK_H_ */