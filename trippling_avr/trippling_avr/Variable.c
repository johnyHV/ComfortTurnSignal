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

uint16_t TimeForEnableAutoFlashing = 200/REFRESH_TIME;
uint16_t TimeForFlashing = 500/REFRESH_TIME;
