/*
 * stm32f4xx_user_cb.c
 *
 *  Created on: May 16, 2019
 *      Author: kriive
 */

#include "stm32f4xx_user_cb.h"
extern uint8_t unitMeasure;
uint64_t lastTick = 0;

void toggleUnitMeasure()
{
	unitMeasure = !unitMeasure;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin) {
	case GEIGERIN: // Interrupt geiger input source pin
		counter++;
		break;
	case GPIO_PIN_5:
		if(HAL_GetTick() >= (lastTick + 50)) {
			lastTick = HAL_GetTick();
			toggleUnitMeasure();
		}
		break;
	default:
		return;
	}
}

