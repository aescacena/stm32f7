/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f7xx.h"
#include "stm32746g_discovery.h"
#include "stm32f7xx_hal_conf.h"

int main(void)
{

	HAL_Init();

	GPIO_InitTypeDef GPIO_InitStructure;

	//Activa CLK de GPIOI llamando a __HAL_RCC_GPIOI_IS_CLK_ENABLED();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_SYSCFG_CLK_ENABLE();

	GPIO_InitStructure.Pin = GPIO_PIN_11;
	GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStructure);

	GPIO_InitTypeDef GPIO_InitStruct_LED;

	/*Configure GPIO pin : PI1 */
	GPIO_InitStruct_LED.Pin = GPIO_PIN_1;
	GPIO_InitStruct_LED.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_LED.Pull = GPIO_NOPULL;
	GPIO_InitStruct_LED.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct_LED);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn,5,0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	while(1){
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, 1);
		HAL_Delay(2000);
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, 0);
		HAL_Delay(2000);
	}
}
void EXTI15_10_IRQHandler(uint16_t GPIO_Pin){

	/*Limpiamos el bit de la interrupción*/
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
	HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);
}

