/*
 * stm32f4xx_user_cb.h
 *
 *  Created on: May 16, 2019
 *      Author: kriive
 */

#ifndef STM32F4XX_USER_CB_H_
#define STM32F4XX_USER_CB_H_
#include "stm32f4xx_hal_gpio.h"

extern uint64_t counter;

#define GEIGERIN 	GPIO_PIN_4

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* STM32F4XX_USER_CB_H_ */
