/** @file Task.h
 *  @brief A System function
 *
 *  System function
 *
 *  @date 11/2/2018 16:59:18
 *  @author Miroslav Pivovarsky (mpivovarsky)
 *  @version 0.1
 *  @bug No know bugs.
 */


#ifndef TASK_H_
#define TASK_H_

#define F_CPU 8000000 //8.0Mhz/8 = 1.0Mhz

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include "Variable.h"

void Flashing(void);
void FlashingLed(struct DirectionalLight *);
void CheckButton(void);
void CheckInput(struct DirectionalLight *);
uint8_t SafetyCheck(void);
uint8_t CheckSetButton();
uint8_t CheckBlinkIntervalJumper();
void WriteTime(uint16_t);
void ReadTime(void);

#endif /* TASK_H_ */