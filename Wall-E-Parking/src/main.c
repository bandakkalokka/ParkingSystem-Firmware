/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f1xx.h"
#include "main.h"

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructA = {0};
  GPIO_InitTypeDef GPIO_InitStructB = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA3 PA4 PA5 PA6
                           PA13 */
  GPIO_InitStructA.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_13;
  GPIO_InitStructA.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructA.Pull = GPIO_NOPULL;
  GPIO_InitStructA.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructA);


  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4*/
  GPIO_InitStructB.Pin = GPIO_PIN_4;
  GPIO_InitStructB.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructB.Pull = GPIO_NOPULL;
  GPIO_InitStructB.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructB);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
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

void segmentDriver(uint8_t digit, uint8_t value){

}

float sensorRead(void){
	uint32_t time, timeout;
	//set trigger low
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_RESET);
	//delay 2us
	HAL_Delay(0.002);
	//trigger high for 10us
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_SET);
	//delay 10us
	HAL_Delay(0.01);
	//trigger low
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_RESET);

	//give some time for response
	timeout = 1000000;
	while(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==0){
		if(timeout-- == 0x00){
			return -1;
		}
	}
	//start time
	time = 0;
	//wait until signal is high
	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) != 1){
		time++;
		//delay 1us;
		HAL_Delay(0.001);
	}
	//return distance in cm
	return (float)time * ((float)0.0171821);
}

float sensorRead2(void){
	uint32_t time, timeout;
	//set trigger low
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_RESET);
	//delay 2us
	HAL_Delay(0.002);
	//trigger high for 10us
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_SET);
	//delay 10us
	HAL_Delay(0.010);
	//trigger low
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_RESET);

	//give some time for response
	timeout = 1000000;
	while(timeout > 0){
		timeout--;
	}
//	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) != 0 || HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) != 1){
//		if(timeout-- == 0x00){
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_SET);
//			return -1;
//		}
//	}

	//start time
	time = 0;
	//wait until signal is high
	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) != 1){
		time++;
		//delay 1us;
		HAL_Delay(0.001);
	}
	//return distance in cm
	return (float)time * ((float)0.0171821);
}

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();

	//Output Test
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_4, GPIO_PIN_SET);  							// Indicator Light, RED, GREEN, BLUE On
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);				// Buzzer On
//	segmentDriver(0, 8);										// DIGIT 0 set to 8
//	segmentDriver(1, 8);										// Digit 1 set to 8
//
//
//	HAL_Delay(1000);		// Delay for 1000ms
//
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_4, GPIO_PIN_RESET);  						// Indicator Light, RED, GREEN, BLUE Off
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);			// Buzzer Off
//	segmentDriver(0, 0);										// DIGIT 0 set to 0
//	segmentDriver(1, 0);										// DIGIT 1 set to 0


	long distance;

//	while(1){
//		//read distance from sensor
//		//distance is returned in cm
//		distance = sensorRead2();
//		if(distance < 0){
//
//		}else if(distance > 50){
//			//more than 50cm
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_SET);
//		}else {
//			//between 0 and 50cm
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_SET);
//		}
//		HAL_Delay(0.1);
//	}

	while(1){
		distance = sensorRead2();
//		if(distance < 0.000005){
		if(distance < 0){
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_SET);
		}else{
			int i = 0;
			while(i < 3){
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_SET);
				HAL_Delay(2000);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_RESET);
				HAL_Delay(2000);
				i++;
			}
		}
	}
//	while(1){
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_RESET);
//		HAL_Delay(2000);
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,GPIO_PIN_SET);
//		HAL_Delay(2000);
//	}
//	while(1){
//		//write a short LOW pulse beforehand to ensure a clean HIGH pulse
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_RESET);
//		HAL_Delay(0.005); //miliseconds
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_SET);
//		HAL_Delay(0.01);
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2,GPIO_PIN_SET);
//	}

//	while(1){
//		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
//		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
//		HAL_Delay(1000);
//	}
}


