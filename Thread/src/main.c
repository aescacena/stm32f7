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
#include "cmsis_os.h"
#include "stdio.h"

static void LED_Thread1(void const *argument);

int main(void)
{
	HAL_Init();

	/*  Thread definition */
	osThreadDef(LED1, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	/* Start thread */
	osThreadCreate(osThread(LED1), NULL);

	/* Start scheduler    */
	osKernelStart();
}

static void LED_Thread1(void const *argument)
{
	GPIO_InitTypeDef GPIO_InitStruct_LED, GPIO_InitStruct_BUTTON;

	/* GPIO Ports Clock Enable */
	__GPIOI_CLK_ENABLE();

	/*Configure GPIO pin : PI1 */
	GPIO_InitStruct_LED.Pin = GPIO_PIN_1;
	GPIO_InitStruct_LED.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_LED.Pull = GPIO_NOPULL;
	GPIO_InitStruct_LED.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct_LED);

	GPIO_InitStruct_BUTTON.Pin = GPIO_PIN_11;
	GPIO_InitStruct_BUTTON.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct_BUTTON.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct_BUTTON);

	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOI, GPIO_PIN_11)){
			HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);
			HAL_Delay(500);
			printf("Pintando \n");
		}
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, 0);

	}
}
