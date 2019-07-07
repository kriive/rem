/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "core/IODevices.h"
#include "core/SysClock.h"
#include "lcddraw.h"

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart2;

uint64_t counter = 0; // 64 bit should be enough

uint8_t unitMeasure = UNIT_CPM;

uint64_t potentiometerValue = 0;

uint64_t counterLimited = 0;

uint64_t cpmShortMeasure = 0;

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure IO Devices */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();

  /* Configure LCD */
  init_LCD();

  uint64_t secondsSinceStartup = 1;

  HAL_ADC_Start_IT(&hadc1);

  /* Infinite loop */
  while (1)
  {
	PulisciSchermo();

	secondsSinceStartup = (uint64_t) HAL_GetTick() / 1000;

	if(secondsSinceStartup == 0) {
		secondsSinceStartup = 1;
	}

	DrawFirstRow(secondsSinceStartup, potentiometerValue, cpmShortMeasure, unitMeasure);
	DrawSecondRow(secondsSinceStartup, counter, unitMeasure);


	HAL_Delay(100);
  }
}

// TODO: find a place for this lonely buddy
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
