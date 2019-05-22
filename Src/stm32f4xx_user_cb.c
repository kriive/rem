/*
 * stm32f4xx_user_cb.c
 *
 *  Created on: May 16, 2019
 *      Author: kriive
 */

#include "stm32f4xx_user_cb.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin) {
	case GEIGERIN: // Interrupt geiger input source pin
		counter++;
		break;
	default:
		return;
	}
}
