/** @file Task.c
 *  @brief A System function
 *
 *  System function
 *
 *  @date 11/2/2018 16:59:18
 *  @author Miroslav Pivovarsky (mpivovarsky)
 *  @version 0.1
 *  @bug No know bugs.
 */

#include "Task.h"

/** @brief Flashing
 *
 *  Bulb flashing
 *
 *  @param void
 *  @return void
*/
void Flashing(void)
{
	FlashingLed(&DirectionalLightLeft);
	FlashingLed(&DirectionalLightRight);
}

/** @brief FlashingLed
 *
 *  specific bulb flashing
 *
 *  @param Light - struct with configuration for specific bulb
 *  @return void
*/
void FlashingLed(struct DirectionalLight *Light)
{
	if (Light->EnableFlashing == TRUE)
	{
		if (Light->CounterFlashing < BLINK_INTERVAL)
		{
			Light->TimerCounterFlashing++;
			
			if (Light->StatusFlashing == BULB_ON)
			{
				if (Light->TimerCounterFlashing > TimeForFlashing)
				{
					Light->TimerCounterFlashing = 0;
					Light->StatusFlashing = BULB_OFF;
					PORTB |= (1 << Light->Led);		// Rele On
					return;
				}
			}
			
			if (Light->StatusFlashing == BULB_OFF)
			{
				if (Light->TimerCounterFlashing > TimeForFlashing)
				{
					Light->TimerCounterFlashing = 0;
					Light->StatusFlashing = BULB_ON;
					Light->CounterFlashing++;
					
					if (Light->CounterFlashing == BLINK_INTERVAL)
					{
						Light->EnableFlashing = FALSE;
						Light->CounterFlashing = 0;
					}
					
					PORTB &= ~(1 << Light->Led);   // Rele Offf
					return;
				}
			}
		}
	}
}

/** @brief CheckButton
 *
 *  Function for check if is trippling not activate
 *
 *  @param void
 *  @return void
*/
void CheckButton(void)
{
	if (SafetyCheck() == FALSE)
	{
		CheckInput(&DirectionalLightLeft);
		CheckInput(&DirectionalLightRight);
	}
}

/** @brief CheckInput
 *
 *  Function for check specific input for actiovation trippling
 *
 *  @param Light - struct with configuration for specific input
 *  @return void
*/
void CheckInput(struct DirectionalLight *Button) {
	// Check Left
	if (!(PINB & (1 << Button->Button))) {
		Button->StartTimerCounterUp = TRUE;
		Button->TimeCountUp++;
	}
	else {
		Button->StartTimerCounterUp = FALSE;
		//Button->TimeCountUp = 0;
	}
	
	if ((Button->EnableFlashing == FALSE) && (Button->StartTimerCounterUp == FALSE)) {
		if ((Button->TimeCountUp > 0) && (Button->TimeCountUp < TimeForEnableAutoFlashing)) {
			Button->EnableFlashing = TRUE;
			Button->StatusFlashing = BULB_ON;
			Button->TimeCountUp = 0;
			Button->CounterFlashing = 0;
			Button->TimerCounterFlashing = 0;
		} else {
			if (Button->TimeCountUp > TimeForEnableAutoFlashing) {
				Button->TimeCountUp = 0;
			}
		}
	}
}

/** @brief SafetyCheck
 *
 *  Safety disable trippling if is activation another direction
 *
 *  @param void
 *  @return uint8_t - status TRUE - safety disable is activate
							 FALSE - safety disable is not activate
*/
uint8_t SafetyCheck(void)
{
	/* Safety disable Right bulb */
	if (!(PINB & (1 << INPUT_LEFT)))
	{
		if (DirectionalLightRight.EnableFlashing == TRUE)
		{
			DirectionalLightRight.TimerCounterFlashing = 0;
			DirectionalLightRight.StatusFlashing = BULB_ON;
			DirectionalLightRight.EnableFlashing = FALSE;
			DirectionalLightRight.CounterFlashing = 0;
			PORTB &= ~(1 << RELE_RIGHT);   // Rele Offf
			return TRUE;
		}
	}
	
	/* Safety disable Left bulb */
	if (!(PINB & (1 << INPUT_RIGHT)))
	{
		if (DirectionalLightLeft.EnableFlashing == TRUE)
		{
			DirectionalLightLeft.TimerCounterFlashing = 0;
			DirectionalLightLeft.StatusFlashing = BULB_ON;
			DirectionalLightLeft.EnableFlashing = FALSE;
			DirectionalLightLeft.CounterFlashing = 0;
			PORTB &= ~(1 << RELE_LEFT);   // Rele Offf
			return TRUE;
		}
	}
	
	return FALSE;
}

/** @brief CheckSetButton
 *
 *  Function for check if is activation configuration button
 *
 *  @param void
 *  @return void
*/
void CheckSetButton()
{
	if (!(PINB & (1 << INPUT_SET_BUTTON)))
	{
		uint8_t InitialStatus = (PINB & (1 << INPUT_LEFT));
		uint16_t BulbStatusCycle = 0;
		uint8_t StartCounter = FALSE;
	
		while (1)
		{
			if (InitialStatus != (PINB & (1 << INPUT_LEFT))) 
			{
				BulbStatusCycle++;
				StartCounter = TRUE;
				_delay_ms(REFRESH_TIME);
			}
			
			if ((StartCounter == TRUE) && (InitialStatus == (PINB & (1 << INPUT_LEFT))))
			{
				WriteTime(BulbStatusCycle);
				while(1)
				{
					wdt_reset();
				}
			}
		}
	}
}

/** @brief WriteTime
 *
 *  Write time to EEPROM
 *
 *  @param CycleTime - Value for write to EEPROM
 *  @return void
*/
void WriteTime(uint16_t CycleTime)
{
	eeprom_write_word(EEPROM_TIME_FLASHING, CycleTime);
}

/** @brief ReadTime
 *
 *  Function for read time for flashing from EEPROM
 *
 *  @param void
 *  @return void
*/
void ReadTime(void)
{
	TimeForFlashing = eeprom_read_word(EEPROM_TIME_FLASHING);
}