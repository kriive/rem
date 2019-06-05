/*
 * stm32f4xx_user_cb.c
 *
 *  Created on: May 16, 2019
 *      Author: kriive
 */

#include "stm32f4xx_user_cb.h"
extern uint8_t unitMeasure;
extern uint64_t counterLimited;

#define GEIGER_ANTIBUMP_TIME	20
#define BUTTON_UNIT_TIME		200

void toggleUnitMeasure()
{
	unitMeasure = !unitMeasure;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin) {
	case GEIGERIN: // Interrupt geiger input source pin
	{ // le graffe servono per definire lo scope della variabile locale lastTick
		// static serve a mantenere il valore tra diverse chiamate alla funzione
		static int lastTick = 0;
		if(HAL_GetTick() >= (lastTick + GEIGER_ANTIBUMP_TIME)) { // antibump
			lastTick = HAL_GetTick();
			counter++;
			counterLimited++;
		}
		break;
	}
	case GPIO_PIN_5:
	{
		static uint64_t lastTick = 0;
		// N.B. only first time lastTick is set to zero!
		// Altre modifiche alla variabile vengono mantenute
		// NON viene inizializzato tutte le volte a 0, grazie alla parolina static

		if(HAL_GetTick() >= (lastTick + BUTTON_UNIT_TIME)) { // antibump
			lastTick = HAL_GetTick();
			toggleUnitMeasure();
		}
		break;
	}
	default:
		return;
	}
}

