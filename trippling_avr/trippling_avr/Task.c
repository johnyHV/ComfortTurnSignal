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
		if (Light->CounterFlashing < BlinkIntervalValue)
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
					
					if (Light->CounterFlashing == BlinkIntervalValue)
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
	// Check input
	if (!(PINB & (1 << Button->Button))) {
		Button->StartTimerCounterUp = TRUE;
		Button->TimeCountUp++;
	}
	else {
		Button->StartTimerCounterUp = FALSE;
		//Button->TimeCountUp = 0;
	}
	
	/* check if is enable flashing, and if is timer OFF */
	if ((Button->EnableFlashing == FALSE) && (Button->StartTimerCounterUp == FALSE)) {
		if ((Button->TimeCountUp > TimeMinimalForEnableAutoFlashing) && (Button->TimeCountUp < TimeForEnableAutoFlashing)) {
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
			ClearStruct();
			PORTB &= ~(1 << RELE_RIGHT);   // Rele Offf
			PORTB &= ~(1 << RELE_LEFT);   // Rele Offf
			_delay_ms(SAFETY_DELAY);
			return TRUE;
		}
	}
	
	/* Safety disable Left bulb */
	if (!(PINB & (1 << INPUT_RIGHT)))
	{
		if (DirectionalLightLeft.EnableFlashing == TRUE)
		{
			ClearStruct();
			PORTB &= ~(1 << RELE_LEFT);   // Rele Offf
			PORTB &= ~(1 << RELE_RIGHT);   // Rele Offf
			_delay_ms(SAFETY_DELAY);
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
*  @return uint8_t
*/
uint8_t CheckSetButton()
{
	/* safety check, if si realy enable configuration jumper, waiting time is 500mS */
	for (uint8_t i=0; i < 10 ;i++)
	{
		if (PINB & (1 << INPUT_SET_BUTTON))
		{
			return 0;
		}
		_delay_ms(50);
	}
	
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
					ReadTime();
					return 1;
					wdt_reset();
				}
			}
		}
	}
	
	return 0;
}

uint8_t CheckBlinkIntervalJumper()
{
	if (!(PINB & (1 << INPUT_SET_BUTTON)))
	{
		/* safety check, if si realy enable configuration jumper, waiting time is 500mS */
		for (uint8_t i=0; i < 10 ;i++)
		{
			if (PINB & (1 << INPUT_SET_BUTTON))
			{
				return 0;
			}
			_delay_ms(50);
		}
		
		if (!(PINB & (1 << INPUT_SET_BUTTON)))
		{
			BlinkIntervalValue = 2;
			return 1;
			
		}
		else
		{
			BlinkIntervalValue = 3;
		}
	}
	else
	{
		BlinkIntervalValue = 3;
	}
	return 0;
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
	TimeForEnableAutoFlashing = (uint16_t) (((TimeForFlashing * REFRESH_TIME) / 100) * 80);
}