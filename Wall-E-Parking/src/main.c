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

TIM_HandleTypeDef htim2;

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
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA3 PA4 PA5 PA6
                           PA13 */
  GPIO_InitStructA.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_13;
  GPIO_InitStructA.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructA.Pull = GPIO_NOPULL;
  GPIO_InitStructA.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructA);


  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4*/
  GPIO_InitStructB.Pin = GPIO_PIN_4;
  GPIO_InitStructB.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructB.Pull = GPIO_NOPULL;
  GPIO_InitStructB.Speed = GPIO_SPEED_FREQ_HIGH;
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

static void MX_TIM2_Init(void)
{

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;			//Set TIM2 to use peripheral clock
	TIM2->PSC = 0;							//Set prescaler to 0
	TIM2->ARR = 80;							//Set ARR 80 (generate 10us pulse)
	//TIM2->CR1 |= TIM_CR1_DIR;					//Set direction to up count
	TIM2->DIER |= TIM_DIER_UIE;					//Enable peripheral to request interrupt
	TIM2->SR &= ~TIM_SR_UIF;					//Clear flag
	//TIM2->CR1 |= TIM_CR1_CEN;					//Start Timer
	NVIC_EnableIRQ(TIM2_IRQn);					//Enable TIM2 Interrupt (NVIC level)

	//TIM2->CR1 |= TIM_CR1_OPM;					//One pulse
	//TIM2->CR1 |= TIM_CR1_CEN;					//Start Timer

}


void segmentDriver(uint8_t digit, uint8_t value){

}

void TIM2_IRQHandler(void)
{
	if(TIM2->SR & TIM_SR_UIF){
		TIM2->SR &= ~TIM_SR_UIF;
		TIM2->CNT = 0;
		//TIM2->ARR = 65535;
		//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
	}

	if(TIM2->SR & TIM_SR_CC2IF){
		TIM2->SR &= ~TIM_SR_CC2IF;
	}
}

void delay_us(uint32_t time){
	TIM2->ARR = 80*time;
	TIM2->CR1 |= TIM_CR1_OPM;					//One pulse
	TIM2->CR1 |= TIM_CR1_CEN;					//Start TIM2
}

long pulseIn(void){

	TIM2->CCMR1 |= TIM_CCMR1_CC2S_1;			//Channel 2 as input
	//TIM2->CCMR1 |= TIM_CCMR1_IC2F_3;			//Ignore first 8 bursts of 40khz
	TIM2->CCER &= ~TIM_CCER_CC2P;				//Non inverted capture on rising edge
	TIM2->CCMR1 |= TIM_CCMR1_IC2PSC_0;			//Input capture prescaler to zero
	TIM2->CCER |= TIM_CCER_CC2E;				//put value of counter in ccr2
	TIM2->DIER |= TIM_DIER_CC1IE;				//enable interrupt request
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	return TIM2->CCR2;
}


int main(void)
{
	HAL_Init();
	SystemClock_Config();
	//RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;
	MX_GPIO_Init();
	MX_TIM2_Init();

	long length;

	while(1){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
		delay_us(10);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_Delay(400);
		//length = pulseIn();
		//if (length > 0)
			//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
		//HAL_Delay(200);

//		if(TIM2->SR & TIM_SR_UIF){
//				TIM2->SR &= ~TIM_SR_UIF;
//				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
//			}
	}
}


