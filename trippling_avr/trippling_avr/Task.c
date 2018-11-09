/*
 * Task.c
 *
 * Created: 11/2/2018 16:59:05
 *  Author: Miroslav Pivovarsky
 */ 

#include "Task.h"

void Flashing(void)
{
	FlashingLed(&DirectionalLightLeft);
	FlashingLed(&DirectionalLightRight);
}

void FlashingLed(struct DirectionalLight *Light)
{
	if (Light->EnableFlashing == TRUE)
	{
		if (Light->CounterFlashing < BLINK_INTERVAL)
		{
			Light->TimerCounterFlashing++;
			
			if (Light->StatusFlashing == BULB_ON)
			{
				if (Light->TimerCounterFlashing > TimeForFlashingOn)
				{
					Light->TimerCounterFlashing = 0;
					Light->StatusFlashing = BULB_OFF;
					PORTB |= (1 << Light->Led);		// Rele On
					return;
				}
			}
			
			if (Light->StatusFlashing == BULB_OFF)
			{
				if (Light->TimerCounterFlashing > TimeForFlashingOn)
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

void CheckButton(void)
{
	if (SafetyCheck() == FALSE)
	{
		CheckInput(&DirectionalLightLeft);
		CheckInput(&DirectionalLightRight);
	}
}

void CheckInput(struct DirectionalLight *Button)
{
	// Check Left
	if (!(PINB & (1 << Button->Button)))
	{
		Button->StartTimerCounterUp = TRUE;
		Button->TimeCountUp++;
	}
	else
	{
		Button->StartTimerCounterUp = FALSE;
	}
	
	if ((Button->EnableFlashing == FALSE) && (Button->StartTimerCounterUp == FALSE))
	{
		if ((Button->TimeCountUp > 0) && (Button->TimeCountUp < TimeForEnableAutoFlashing))
		{
			Button->EnableFlashing = TRUE;
			Button->StatusFlashing = BULB_ON;
			Button->TimeCountUp = 0;
			Button->CounterFlashing = 0;
			Button->TimerCounterFlashing = 0;
		}
	}
}

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

void MeasureTime(void)
{
	volatile uint8_t Edata = eeprom_read_byte(0x00);
	eeprom_write_byte(0x00, 10);
	Edata = eeprom_read_byte(0x00);
}