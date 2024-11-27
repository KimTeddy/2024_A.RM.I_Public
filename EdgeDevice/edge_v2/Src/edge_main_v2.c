/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "crc.h"
#include "dcmi.h"
#include "dma.h"
#include "i2c.h"
#include "memorymap.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "app_x-cube-ai.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "armi_gpio.h"
#include "armi_adc.h"
#include "armi_uart.h"
#include "armi_dcmi.h"
#include "armi_rf.h"
#include "armi_relay.h"

#include "nrf24l01p.h"

#include "ov2640.h"

#include "stm32ipl.h"
#include "network.h"
//#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//DCMI
extern uint8_t armi_sccb_failure_count;
//AI
bool armi_isperson = false;
bool armi_islowbatt = false;
extern ai_u8 *data_outs[AI_NETWORK_OUT_NUM];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI4_Init();
  MX_USART1_UART_Init();
  MX_DCMI_Init();
  MX_ADC1_Init();
  MX_I2C2_Init();
  MX_CRC_Init();
  MX_X_CUBE_AI_Init();
  /* USER CODE BEGIN 2 */
	//while (1)
		//armi_led_test();

		//standby_mode();
	armi_init_1_start();

	armi_get_devnum();
	armi_init_2_rf();
	//while (1)
		armi_led_test();
	//standby_mode();

	//----------------------------------------------
	//while(1);
	/*1. RAW IMAGE SENSOR SETTING & CAPTURE*/
	armi_led(R, 1);
	armi_init_3_ov2640(DCMI_RAW);
	armi_led(R, 0);

	armi_led(R, 1);
	armi_led(G, 1);
	armi_led(B, 1);
	camera_capture(DCMI_RAW);
	//my_printf("\r\n\r\n");
	armi_led(R, 0);
	armi_led(G, 0);
	armi_led(B, 0);

	HAL_GPIO_WritePin(POW_EN_GPIO_Port, POW_EN_Pin, GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(POW_EN_GPIO_Port, POW_EN_Pin, GPIO_PIN_SET);
	HAL_Delay(50);

	/*2. JPEG IMAGE SENSOR SETTING & CAPTURE*/
	armi_led(R, 1);
	armi_init_3_ov2640(DCMI_JPEG);
	armi_led(R, 0);

	armi_led(R, 1);
	armi_led(G, 1);
	camera_capture(DCMI_JPEG);
	my_printf("\r\n\r\n");
	armi_led(R, 0);
	armi_led(G, 0);

	/*3. NEURAL NETWORK & Batt Check*/
	armi_led(G, 1);
	//MX_X_CUBE_AI_Process();
	armi_isperson = true;

	if (armi_batt_lower_than_mv(3500)) {
		armi_islowbatt = true;
		armi_led(1, 1);
	}
	armi_led(G, 0);

	/*4. IF PERSON || LowBatt -> RF SETTTING & TX DATA -> 5*/
	armi_led(G, 1);
	armi_led(B, 1);
	for (int idx = 0; idx < AI_NETWORK_OUT_NUM; idx++) {
		if (*data_outs[idx] > 128) {
			armi_isperson = true;
			armi_led(3, 1);
#ifdef DEBUG
			my_printf("\r\nHuman Detected!\r\n");
#endif
			break;
		}
	}
	armi_led(G, 0);
	armi_led(B, 0);

	if (armi_isperson || armi_islowbatt) {
		armi_led(B, 1);

		armi_led(R, 1);
		armi_init_2_rf();
		armi_led(R, 0);

		if (armi_isperson) {
			armi_led(4, 1);
			armi_image_tx();
			armi_led(4, 0);
		}
		if (armi_islowbatt) {
			armi_led(4, 1);

			armi_led(4, 0);
		} //+++++++++

		armi_led(B, 0);
	}
	//________________________________________________
	/*5. IF NOT PERSON||LowBatt||END -> STANDBY MODE*/
#ifdef DEBUG
	my_printf("____Standby Mode____\r\n");
#endif
	standby_mode();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */

  MX_X_CUBE_AI_Process();
    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /*AXI clock gating */
  RCC->CKGAENR = 0xFFFFFFFF;

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 11;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO2, RCC_MCO2SOURCE_HSE, RCC_MCODIV_2);
}

/* USER CODE BEGIN 4 */
//INIT
void armi_init_1_start() {
#ifdef DEBUG
//UART_TX
	HAL_UART_Transmit(&huart1, str_hello, sizeof(str_hello), 100);
	my_printf("[Object Detected]\r\n");
#endif
//Power Enable & PIR Disable
	HAL_GPIO_WritePin(POW_EN_GPIO_Port, POW_EN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PIR_ENn_GPIO_Port, PIR_ENn_Pin, GPIO_PIN_SET);
	HAL_Delay(50);

	OV2640_Init(&hi2c2, &hdcmi);
	HAL_Delay(10);
}

void armi_init_2_rf() {
//nrf24l01p_TX
	//nrf24l01p_tx_init(2500, _2Mbps);
	//armi_rf_set(RF_RX);
	//HAL_Delay(10);
}

void armi_init_3_ov2640(uint8_t rawjpeg) {
//OV2640
	armi_sccb_failure_count = 0;
	if (rawjpeg > 0)	//jpeg = 1
		OV2640_ResolutionOptions(imgRes, rawjpeg);
	else
		OV2640_ResolutionOptions(imgRes_raw, rawjpeg); //raw = 0
	HAL_Delay(10);
	OV2640_AdvancedWhiteBalance();
#ifdef DEBUG
	my_printf("\r\nfail count=%d", armi_sccb_failure_count);
#endif
	if (armi_sccb_failure_count > ARMI_SCCB_FAILURE_NUM) {
#ifdef DEBUG
		my_printf("OV2640 Resetting..\r\n");
#endif
		NVIC_SystemReset();
	}
#ifdef DEBUG
	my_printf(", 42 is Default.\r\n");
#endif
}

//STANDBY MODE
void standby_mode() {
//__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnterSTANDBYMode();
}
/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
