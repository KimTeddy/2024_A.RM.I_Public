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
#include "dcmi.h"
#include "gpdma.h"
#include "i2c.h"
#include "icache.h"
#include "memorymap.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "app_x-cube-ai.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ov2640.h"
#include "linked_list.h"

#include "nrf24l01p.h"

#include "stm32ipl.h"
#include "image.h"


#include "network.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern DMA_QListTypeDef DCMIQueue;
extern ai_u8 *data_outs[AI_NETWORK_OUT_NUM];
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#undef DEBUG
//LED Color
#define RED 0
#define GREEN 1

//#define RES160X120
#define RES320X240
//#define RES640X480
//#define RES800x600
//#define RES1024x768
//#define RES1280x960

#define ARMI_SCCB_FAILURE_NUM 42
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#ifdef RES160X120
enum imageResolution imgRes=RES_160X120;
int imgRes_2 = 160 * 120 / 2;
uint8_t frameBuffer[RES_160X120] = { 0 };
#endif

#ifdef RES320X240
enum imageResolution imgRes = RES_320X240;
int imgRes_2 = 320 * 240;
uint8_t frameBuffer[76800] = { 0 };
#endif

#ifdef RES640X480
enum imageResolution imgRes = RES_640X480;
int imgRes_2 = 640 * 480 / 2;
uint16_t frameBuffer[RES_640X480] = { 0 };
#endif

#ifdef RES800x600
enum imageResolution imgRes=RES_800x600;
int imgRes_2 = 800 * 600 / 2;
uint8_t frameBuffer[RES_800x600] = { 0 };
#endif

#ifdef RES1024x768
enum imageResolution imgRes=RES_1024x768;
int imgRes_2 = 1024 * 768 / 2;
uint8_t frameBuffer[RES_1024x768] = { 0 };
#endif

#ifdef RES1280x960
enum imageResolution imgRes = RES_1280x960;
int imgRes_2 = 1280 * 960 / 2;
uint16_t frameBuffer[RES_1280x960] = { 0 };
#endif
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//adc
uint16_t adc_value;
uint16_t batt_mv;
//char batt_volt_str[10];
//uint8_t *adc_str;
/*************************************************************/
//OV2640
unsigned short mutex = 1;
uint32_t bufferPointer = 76800;
unsigned short headerFound = 0;

extern uint8_t armi_sccb_failure_count;
//nrf24l01p
uint8_t tx_data[NRF24L01P_PAYLOAD_LENGTH] = { 0, 1, 2, 3, 4, 5, 6, 7 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemPower_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef DEBUG
uint8_t str_hello[] = "\n\r<Hello A.RM.I>\n\r";
#endif
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* Configure the System Power */
	SystemPower_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_GPDMA1_Init();
	MX_DCMI_Init();
	MX_ICACHE_Init();
	MX_USART1_UART_Init();
	MX_SPI1_Init();
	MX_I2C1_Init();
	MX_ADC1_Init();
	MX_ADC2_Init();
	MX_X_CUBE_AI_Init();
	/* USER CODE BEGIN 2 */
	//gibon setting
	HAL_Delay(10);
	armi_init_first();

	camera_capture();
	HAL_Delay(50);
	camera_capture();

	armi_init_second();
	//battery volt check
	armi_check_lowbattery();

	armi_led_blink(RED, 50);

	HAL_GPIO_WritePin(DCMI_PWDN_GPIO_Port, DCMI_PWDN_Pin, GPIO_PIN_SET);
	OV2640_StopDCMI();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		MX_X_CUBE_AI_Process();
		/* USER CODE BEGIN 3 */

		for (int idx = 0; idx < AI_NETWORK_OUT_NUM; idx++) {
			if (*data_outs[idx] > 128) {
#ifdef DEBUG
				my_printf("\r\nHuman Detected!\r\n", *data_outs[idx]);
				HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin,
						GPIO_PIN_SET);
				HAL_Delay(5000);
#endif
			}
		}
#ifdef DEBUG
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
		my_printf("____Standby Mode____\r\n");
		HAL_GPIO_WritePin(DCMI_RST_GPIO_Port, DCMI_RST_Pin, GPIO_PIN_RESET);
#endif
		HAL_Delay(10);
		standby_mode();
	}
	/* USER CODE END 3 */
}

//in while
//		image_t src_img;
//		image_t dst_img;
//
//		src_img.w = 224;
//		src_img.h = 224;
//		src_img.bpp = IMAGE_BPP_RGB565;
//		src_img.data = img_000;
//
//		dst_img.w = 224;
//		dst_img.h = 224;
//		dst_img.bpp = IMAGE_BPP_RGB888;
//
//		bool reverse = false;

//		my_printf("\n\r");
//		my_printf("reverse: %d\n\r", reverse);
//		STM32Ipl_ConvertRev(&src_img, &dst_img, reverse);
//
//		//my_printf("source: ");
//		for (int i = 0; i < 5; i++) {
//			my_printf("0x%02x, ", src_img.data[i]);
//		}
//		//my_printf("\n\r");
//		//my_printf("destination: ");
//		for (int i = 0; i < 5; i++) {
//			my_printf("0x%02x, ", dst_img.data[i]);
//		}
//my_printf("\n\r");
//MX_X_CUBE_AI_Process_ARMI(dst_img.data);

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1)
			!= HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI
			| RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
	RCC_OscInitStruct.PLL.PLLM = 3;
	RCC_OscInitStruct.PLL.PLLN = 10;
	RCC_OscInitStruct.PLL.PLLP = 8;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 1;
	RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
	RCC_OscInitStruct.PLL.PLLFRACN = 0;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_PCLK3;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief Power Configuration
 * @retval None
 */
static void SystemPower_Config(void) {
	HAL_PWREx_EnableVddIO2();

	/*
	 * Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
	 */
	HAL_PWREx_DisableUCPDDeadBattery();

	/*
	 * Switch to SMPS regulator instead of LDO
	 */
	if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN PWR */
	/* USER CODE END PWR */
}

/* USER CODE BEGIN 4 */
#undef DEBUG
void armi_init_first() {
//Power Enable & PIR Disable
	HAL_GPIO_WritePin(POW_EN_GPIO_Port, POW_EN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(PIR_NEN_GPIO_Port, PIR_NEN_Pin, GPIO_PIN_SET);
	HAL_Delay(50);
//DCMI, DMA
	MX_DCMIQueue_Config();
	HAL_DMAEx_List_LinkQ(&handle_GPDMA1_Channel12, &DCMIQueue);
	__HAL_LINKDMA(&hdcmi, DMA_Handle, handle_GPDMA1_Channel12);
	HAL_Delay(10);
//OV2640
	armi_sccb_failure_count = 0;
	OV2640_Init(&hi2c1, &hdcmi);
	HAL_Delay(10);
	OV2640_ResolutionOptions(imgRes);
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

void armi_init_second() {
#ifdef DEBUG
//UART_TX
	HAL_HalfDuplex_EnableTransmitter(&huart1);
	HAL_Delay(10);
	HAL_UART_Transmit(&huart1, str_hello, sizeof(str_hello), 100);
	my_printf("[Object Detected]\r\n");
#endif
//nrf24l01p_TX
	nrf24l01p_tx_init(2500, _1Mbps);
	HAL_Delay(10);
}
//	OV2640_Brightness(Brightness_2);
//	HAL_Delay(10);
//	OV2640_Saturation(Saturation_2);
//	HAL_Delay(10);
//	OV2640_Contrast(Contrast_2);
//	HAL_Delay(10);
//	OV2640_SpecialEffect(Bluish);
//	HAL_Delay(10);
//	OV2640_LightMode(Auto);
//	HAL_Delay(10);

//HAL_UART_Transmit(&huart1, str_hello, sizeof(str_hello), 100);
//sprintf(batt_volt_str, "%f", batt_volt);
//HAL_UART_Transmit(&huart1, adc_str, sizeof(adc_str), 100);

//do {
//	armi_sccb_failure_count = 0;
//	OV2640_Init(&hi2c1, &hdcmi);
//	HAL_Delay(50);
//	OV2640_ResolutionOptions(imgRes);
//	HAL_Delay(50);
//#ifdef DEBUG
//	my_printf("\r\nfail number=%d \r\n", armi_sccb_failure_count);
//#endif
//} while (armi_sccb_failure_count > ARMI_SCCB_FAILURE_NUM);

void armi_led_blink(uint8_t color, int delay) {
	if (color == RED) {	//LED_RED one blink
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		HAL_Delay(delay);
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
		HAL_Delay(delay);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
	}
}

void armi_check_lowbattery() {
	if (batt_lower_than_mv(3000) > 0) {
		// transmit
		for (int i = 0; i < 8; i++) {
			tx_data[i]++;
			nrf24l01p_tx_transmit(tx_data);
			HAL_Delay(100);
		}
	}
}

//OV2640
void vprint(const char *fmt, va_list argp) {
	char string_v[115200];
	if (0 < vsprintf(string_v, fmt, argp)) // build string
			{
		HAL_UART_Transmit(&huart1, (uint8_t*) string_v, strlen(string_v),
				0xffffff); // send message via UART
	}
}

void my_printf(const char *fmt, ...) // custom printf() function
{
	va_list argp;
	va_start(argp, fmt);
	vprint(fmt, argp);
	va_end(argp);
}

void camera_capture() {
#ifdef DEBUG
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
	for (int i = 0; i < imgRes_2; i++)
		frameBuffer[i] = 0;
	//my_printf("captured %02x", frameBuffer[imgRes_2-1]);
#endif
//	if (HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin)) {
	if (mutex == 1) {
		memset(frameBuffer, 0, sizeof frameBuffer);
		OV2640_CaptureSnapshot((uint32_t) frameBuffer, imgRes_2);
#ifdef DEBUG
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
		//my_printf("FirstFB %3d | Middle %3d | last %3d ", frameBuffer[0], frameBuffer[imgRes_2/2], frameBuffer[imgRes_2-1]);
#endif
//		while (1) {
//			if (headerFound == 0 && frameBuffer[bufferPointer] == 0xFF
//					&& frameBuffer[bufferPointer + 1] == 0xD8) {
//				headerFound = 1;
//#ifdef DEBUG
//				my_printf("Found header of JPEG file \r\n");
//#endif
//			}
//			if (headerFound == 1 && frameBuffer[bufferPointer] == 0xFF
//					&& frameBuffer[bufferPointer + 1] == 0xD9) {
//				bufferPointer = bufferPointer + 2;
//#ifdef DEBUG
//				my_printf("Found EOF of JPEG file \r\n");
//#endif
//				headerFound = 0;
//				break;
//			}
//
//			if (bufferPointer >= 115200) {
//				break;
//			}
//			bufferPointer++;
//		}
//#ifdef DEBUG
//		my_printf("Image size: %d bytes \r\n", bufferPointer);
//		for (int i = 0; i < bufferPointer; i++)
//			my_printf("%02x", frameBuffer[i]);
//#endif

		//bufferPointer = 0;
	}
//		mutex = 0;
//	} else {
//		mutex = 1;
//	}
}

/*************************************************************/
//ADC
uint8_t batt_lower_than_mv(int batt_limit) {
	HAL_ADC_Start(&hadc1);
	if (HAL_ADC_PollForConversion(&hadc1, 240) == HAL_OK) {
		adc_value = HAL_ADC_GetValue(&hadc1);
	}
	HAL_ADC_Stop(&hadc1);

	batt_mv = (int) ((adc_value / 16383.0) * 3300 * 2);

#ifdef DEBUG
	//my_printf("adc_value=%d, batt_mv=%d mV\n\r", adc_value, batt_mv);
	my_printf("Battery: %d mV\n\r", batt_mv);
#endif
	if (batt_mv < batt_limit) //low battery 3000
			{
		return 1;
	} else {
		return 0;
	}
}
//UART1_print_2_byte_number(adc_value);
//HAL_UART_Transmit(&huart1, (char *) "\n", 2, 100);
//UART1_print_2_byte_float(batt_mv);
//UART1_print_2_byte_float(batt_volt);
/*************************************************************/
//STANDBY MODE
void standby_mode() {
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnterSTANDBYMode();
}
/*************************************************************/
//Interrupt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == NRF24L01P_IRQ_PIN_NUMBER) {
		nrf24l01p_tx_irq();
	}
}
/*************************************************************/
/*************************************************************/
#ifdef DEBUGx
//UART
void UART1_print_2_byte_number(uint16_t n) {
	uint8_t numString[8];
	int i = 0, length = 0;

	if (n == 0) {
		numString[i++] = '0';
	} else {
		while (n != 0) {
			numString[i++] = n % 10 + '0';
			n = n / 10;
		}
	}
	numString[i] = '\0';
	length = i;

	for (int j = 0; j < length / 2; j++) {
		uint8_t temp = numString[j];
		numString[j] = numString[length - j - 1];
		numString[length - j - 1] = temp;
	}

	HAL_UART_Transmit(&huart1, numString, length, 100);
}

void UART1_print_2_byte_float(uint16_t n) {
	uint8_t numString[8];
	int i = 0, length = 0;

	if (n == 0) {
		numString[i++] = '0';
	} else {
		while (n != 0) {
			if (i == 3)
				numString[i] = '.';
			else {
				numString[i] = n % 10 + '0';
				n = n / 10;
			}
			i++;
		}
	}
	numString[i] = '\0';
	length = i;

	for (int j = 0; j < length / 2; j++) {
		uint8_t temp = numString[j];
		numString[j] = numString[length - j - 1];
		numString[length - j - 1] = temp;
	}

	HAL_UART_Transmit(&huart1, numString, length, 100);
}
#endif
/* USER CODE END 4 */

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
