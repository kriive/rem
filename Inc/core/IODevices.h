/*
 * IODevices.h
 *
 *  Created on: Jun 5, 2019
 *      Author: kriive
 */

#ifndef CORE_IODEVICES_H_
#define CORE_IODEVICES_H_

#include "stm32f4xx_hal.h"

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define Potentiometer_Pin GPIO_PIN_1
#define Potentiometer_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define ExtLight_Pin GPIO_PIN_10
#define ExtLight_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define ImpulseInput_Pin GPIO_PIN_4
#define ImpulseInput_GPIO_Port GPIOB
#define ImpulseInput_EXTI_IRQn EXTI4_IRQn
#define ChangeUnit_Pin GPIO_PIN_5
#define ChangeUnit_GPIO_Port GPIOB
#define ChangeUnit_EXTI_IRQn EXTI9_5_IRQn

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void);

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART2_UART_Init(void);

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
void MX_ADC1_Init();

#endif /* CORE_IODEVICES_H_ */
