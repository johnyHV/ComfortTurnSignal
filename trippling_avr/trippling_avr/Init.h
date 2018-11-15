/** @file Init.h
 *  @brief A System function
 *
 *  Inicialization function
 *
 *  @date 11/2/2018 13:59:51
 *  @author Miroslav Pivovarsky (mpivovarsky)
 *  @version 0.1
 *  @bug No know bugs.
 */

#ifndef INIT_H_
#define INIT_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include "Variable.h"

void initTimer1(void);
void initInterruptGpio(void);
void initGpioPin(void);

#endif /* INIT_H_ */