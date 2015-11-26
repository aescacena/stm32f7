/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "main.h"
#include "stm32f7xx.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_sd.h"

static void CPU_CACHE_Enable(void);
static void SystemClock_Config(void);
static void Display_Description(void);

int main(void){

	uint8_t  lcd_status = LCD_OK;

	CPU_CACHE_Enable();

	HAL_Init();

	/* Configura el reloj del sistema en 200 Mhz */
	SystemClock_Config();

	BSP_LED_Init(LED1);

	/*Configura el botón de usuario en modo GPIO*/
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

	/*Inicializar LCD*/
	lcd_status = BSP_LCD_Init();
	if(lcd_status != LCD_OK)
		while(1);

	/*Inicializa LCD Layers*/
	BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);

	Display_Description();

	uint8_t detectSD = 0;
	uint8_t SD_state = MSD_OK;

	while(1){
		if(BSP_PB_GetState(BUTTON_KEY) != 0){
			HAL_Delay(500);
			Display_Description();
			detectSD = 1;
		}
		if(detectSD){
			detectSD = 0;
			SD_state = BSP_SD_Init();
			if(SD_state != MSD_OK){
				BSP_LCD_ClearStringLine(11);
				BSP_LCD_ClearStringLine(12);
				BSP_LCD_DisplayStringAt(0, (BSP_LCD_GetYSize()/2.5)+25, (uint8_t *)"Tarjeta SD no encontrada", CENTER_MODE);
			}
			else{
				BSP_LCD_ClearStringLine(11);
				BSP_LCD_ClearStringLine(12);
				BSP_LCD_DisplayStringAt(0, (BSP_LCD_GetYSize()/2.5)+25, (uint8_t *)"Tarjeta SD encontrada", CENTER_MODE);
			}
		}
	}
}

/**
 * @brief  Check for user input.
 * @param  None
 * @retval Input state (1 : active / 0 : Inactive)
 */
uint8_t CheckForUserInput(void){

	if (BSP_PB_GetState(BUTTON_KEY) != RESET)
	{
		HAL_Delay(10);
		while (BSP_PB_GetState(BUTTON_KEY) != RESET);
		return 1 ;
	}
	return 0;
}

/**
 * @brief  CPU L1-Cache enable.
 *         Invalidate Data cache before enabling
 *         Enable Data & Instruction Cache
 * @param  None
 * @retval None
 */
static void CPU_CACHE_Enable(void){

	(*(uint32_t *) 0xE000ED94) &= ~0x5;
	(*(uint32_t *) 0xE000ED98) = 0x0; //MPU->RNR
	(*(uint32_t *) 0xE000ED9C) = 0x20010000 |1<<4; //MPU->RBAR
	(*(uint32_t *) 0xE000EDA0) = 0<<28 | 3 <<24 | 0<<19 | 0<<18 | 1<<17 | 0<<16 | 0<<8 | 30<<1 | 1<<0 ; //MPU->RASE  WT
	(*(uint32_t *) 0xE000ED94) = 0x5;

	/* Invalidate I-Cache : ICIALLU register*/
	SCB_InvalidateICache();

	/* Enable branch prediction */
	SCB->CCR |= (1 <<18);
	__DSB();

	/* Enable I-Cache */
	SCB_EnableICache();

	/* Enable D-Cache */
	SCB_InvalidateDCache();
	SCB_EnableDCache();
}

static void SystemClock_Config(void){

	HAL_StatusTypeDef ret = HAL_OK;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 400;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 8;
	ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
	//ASSERT(ret != HAL_OK);
	if(ret != HAL_OK)
		while(1);

	/* activate the OverDrive to reach the 180 Mhz Frequency */
	ret = HAL_PWREx_ActivateOverDrive();
	//  ASSERT(ret != HAL_OK);
	if(ret != HAL_OK)
		while(1);

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
	//  ASSERT(ret != HAL_OK);
	if(ret != HAL_OK)
		while(1);
}

static void Display_Description(void){

	/* Set LCD Foreground Layer  */
	BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

	/* Clear the LCD */
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);//Fondo de letras
	BSP_LCD_Clear(LCD_COLOR_WHITE);//Fondo de pantalla

	/* Set the LCD Text Color */
	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);

	/* Display LCD messages */
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2.5, (uint8_t *)"Detector de SD", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, (BSP_LCD_GetYSize()/2.5)+25, (uint8_t *)"Buscando...", CENTER_MODE);

	/* Draw Bitmap */
	//BSP_LCD_DrawBitmap((BSP_LCD_GetXSize() - 80) / 2, 65, (uint8_t *)stlogo);

	BSP_LCD_SetFont(&Font12); //Tamaño de letra
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 20, (uint8_t *)"Diseno Microcontroladores. Universidad De Sevilla", CENTER_MODE);
}
