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
#include "memorymap.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "nrf24l01p.h"
//#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RF_TX false
#define RF_RX true
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
bool armi_rf_mode = RF_RX;

uint8_t rx_data[NRF24L01P_PAYLOAD_LENGTH] = { 'q', };
uint8_t tx_data_ok[NRF24L01P_PAYLOAD_LENGTH] = "4OK";
uint8_t tx_data_no[NRF24L01P_PAYLOAD_LENGTH] = "4NO";
uint8_t tx_data_fin[NRF24L01P_PAYLOAD_LENGTH] = "FIN";
uint8_t test_data[NRF24L01P_PAYLOAD_LENGTH] = { 'A', 'R', 'M', 'I', '!', '\r',
		'\n', '\0' };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */
void armi_rf_set(bool rf_mode);
void armi_rf_dir(bool rf_mode);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

void vprint(const char *fmt, va_list argp) {
	char string_v[65535];
	if (0 < vsprintf(string_v, fmt, argp)) // build string
			{
		HAL_UART_Transmit(&huart1, (uint8_t*) string_v, strlen(string_v),
				0xffffff); // send message via UART
		//CDC_Transmit_HS(string_v, sizeof(string_v));
	}
}

void my_printf(const char *fmt, ...) // custom printf() function
{
	va_list argp;
	va_start(argp, fmt);
	vprint(fmt, argp);
	va_end(argp);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int ok = 0;
int num = 1;
int row = 0;
int fin = 0;
uint8_t image_rx[65535] = { 0, };
bool armi_img_rx_fin = 0;

#define MAX_CAPTURES 20  // Define the maximum number of captures

volatile uint32_t captured_values[MAX_CAPTURES] = { 0 }; // Array to store multiple captured values
volatile uint32_t captured_overflow_counts[MAX_CAPTURES] = { 0 }; // Array to store overflow count at capture time
volatile uint32_t overflow_count = 0;
volatile uint8_t capture_index = 0;  // Index to keep track of captures

uint64_t captured_times[MAX_CAPTURES] = { 0 };

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM2) {
		overflow_count++;  // Increment overflow count
	}
}

void armi_start_capture(void) {
	overflow_count = 0;  // Initialize overflow count
	capture_index = 0;    // Reset capture index
	__HAL_TIM_SET_COUNTER(&htim2, 0);  // Reset timer counter
	HAL_TIM_Base_Start_IT(&htim2); // Start timer base with interrupt for overflow counting
}

uint64_t armi_get_capture_time_ns(uint8_t index) {
	if (index >= MAX_CAPTURES)
		return 0;  // Check for valid index
	uint64_t total_ns = ((uint64_t) captured_overflow_counts[index]
			* 4294967296ULL + captured_values[index]) * 4; // Convert to 4ns units
	return total_ns;
}

void armi_capture() {
// Periodically capture timer values
	if (capture_index < MAX_CAPTURES) {
		captured_values[capture_index] = __HAL_TIM_GET_COUNTER(&htim2); // Capture timer counter
		captured_overflow_counts[capture_index] = overflow_count; // Store overflow count at capture time
		captured_times[capture_index] = armi_get_capture_time_ns(capture_index);
		capture_index++;  // Increment capture index
	}
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

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
	MX_SPI4_Init();
	MX_USART1_UART_Init();
	MX_TIM2_Init();
	/* USER CODE BEGIN 2 */
	/* USER CODE BEGIN 2 */
	//my_printf("start\r\n");
	//HAL_GPIO_WritePin(USB_CONSIG_GPIO_Port, USB_CONSIG_Pin, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
	//HAL_Delay(500);
	//HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
	//HAL_Delay(500);

	//uint8_t text[] = "A.RM.I SERVER\n\r";
	//my_printf("A.RM.I SERVER\r\n");
	//CDC_Transmit_HS(text, sizeof(text));
	//HAL_Delay(500);

	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	nrf24l01p_rx_init(2500, _2Mbps);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		//num++;
		armi_rf_set(RF_RX);
		HAL_Delay(10);
		while (rx_data[0] != num) {
			//armi_rf_dir(RF_RX);
			//nrf24l01p_rx_receive(rx_data);
			//HAL_Delay(1);
			if (rx_data[0] == ((num - 1) == 0 ? 9 : num - 1)) {

				//my_printf("%s\r\n", &rx_data[1]);
				rx_data[0] = 'q';
				tx_data_ok[0] = ((num - 1) == 0 ? 9 : num - 1);

				//my_printf("tx: %s\r\n", tx_data_ok);
				armi_rf_set(RF_TX);
				for (int i = 0; i < 15; i++) {
					nrf24l01p_tx_transmit(tx_data_ok);
					HAL_Delay(1);
				}
				armi_rf_set(RF_RX);
			}
			//if (rx_data[0] != num + '0' && ) {
			//   armi_rf_dir(RF_TX);
			//   nrf24l01p_tx_transmit(tx_data_ok);
			//}
		}

		//my_printf("Check Num: %c, ", rx_data[0]);

		if (rx_data[0] == (num)) {
			HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);

			//my_printf("%s\r\n", &rx_data[1]);
			rx_data[0] = 'q';
			tx_data_ok[0] = num;

			//my_printf("tx: %s\r\n", tx_data_ok);
			armi_rf_set(RF_TX);
			for (int i = 0; i < 10; i++) {
				nrf24l01p_tx_transmit(tx_data_ok);
				HAL_Delay(1);
			}
			//sprintf(&image_rx[row], "%s", &rx_data[1]);
			for (int i = 0; i < 30; i++) {
				image_rx[row + i] = rx_data[i + 1];
			}
			for (fin = 0; fin < 31; fin++) {
				//if(image_rx[row+fin]=='f'&&image_rx[row+fin+1]=='f'&&image_rx[row+fin+2]=='d'&&image_rx[row+fin+3]=='9'){
				if (image_rx[row + fin - 2] == 0xFF
						&& image_rx[row + fin - 1] == 0xD9) {
					image_rx[row + fin] = 'J';

					my_printf("tx: %s\r\n", tx_data_fin);
					armi_rf_set(RF_TX);
					for (int i = 0; i < 50; i++) {
						nrf24l01p_tx_transmit(tx_data_fin);
						HAL_Delay(1);
					}
					for (int i = 0; i < row + fin; i++)
						my_printf("%02x", image_rx[i]);
					armi_img_rx_fin = 1;
					break;
				}
			}
			if (armi_img_rx_fin > 0) {
				image_rx[row + fin] = '\0';

				row = 0;
				num = 1;
				fin = 0;
				armi_img_rx_fin = 0;

				continue;
			}
			row += 30;
			num++;
			if (num > 9)
				num = 1;

			//HAL_UART_Transmit(&huart3, (uint8_t*) rx_data, strlen(rx_data),
			//      0xffffff); // send message via UART
			//HAL_UART_Transmit(&huart3, (uint8_t*) "\r\n", strlen("\r\n"), 0xffffff); // send message via UART
		}
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/*AXI clock gating */
	RCC->CKGAENR = 0xFFFFFFFF;

	/** Supply configuration update enable
	 */
	HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

	while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {
	}

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
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1
			| RCC_CLOCKTYPE_D1PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
	RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */
void armi_rf_set(bool rf_mode) {
	if (rf_mode != armi_rf_mode) {
		if (rf_mode == RF_TX)
			nrf24l01p_tx_init(2500, _2Mbps);
		else
			nrf24l01p_rx_init(2500, _2Mbps);
		armi_rf_mode = rf_mode;
	}
}
void armi_rf_dir(bool rf_mode) {
	if (rf_mode != armi_rf_mode) {
		if (rf_mode == RF_TX)
			nrf24l01p_ptx_mode();
		else
			nrf24l01p_prx_mode();
		armi_rf_mode = rf_mode;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == NRF24L01P_IRQ_PIN_NUMBER) {
//		HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
		//nrf24l01p_rx_receive(rx_data);
		if (armi_rf_mode == RF_TX){
//			HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
//			HAL_Delay(100);
			nrf24l01p_tx_irq();
		}
		else {
//			HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
//			nrf24l01p_rx_receive(rx_data);
		}
	}
}
/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void) {
	MPU_Region_InitTypeDef MPU_InitStruct = { 0 };

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
void Error_Handler(void) {
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
