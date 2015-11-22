#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

void MX_GPIO_Init(void);

int main(void)
{

	HAL_Init();

	MX_GPIO_Init();

	while(1) {
		if(HAL_GPIO_ReadPin(GPIOI, GPIO_PIN_11)){
			HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);
			HAL_Delay(500);
		}
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, 0);
	}
}

void MX_GPIO_Init(void)
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
}
