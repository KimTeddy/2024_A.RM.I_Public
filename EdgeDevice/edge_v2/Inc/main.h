/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void armi_init_1_start();
void armi_init_2_rf();
void armi_init_3_ov2640(uint8_t rawjpeg);

void standby_mode();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADDR0_Pin GPIO_PIN_0
#define ADDR0_GPIO_Port GPIOA
#define ADDR1_Pin GPIO_PIN_1
#define ADDR1_GPIO_Port GPIOA
#define ADDR2_Pin GPIO_PIN_2
#define ADDR2_GPIO_Port GPIOA
#define ADDR3_Pin GPIO_PIN_3
#define ADDR3_GPIO_Port GPIOA
#define PIR_ENn_Pin GPIO_PIN_5
#define PIR_ENn_GPIO_Port GPIOC
#define BATT_Pin GPIO_PIN_1
#define BATT_GPIO_Port GPIOB
#define NRF_IRQ_Pin GPIO_PIN_9
#define NRF_IRQ_GPIO_Port GPIOE
#define NRF_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define NRF_CE_Pin GPIO_PIN_10
#define NRF_CE_GPIO_Port GPIOE
#define NRF_CSN_Pin GPIO_PIN_11
#define NRF_CSN_GPIO_Port GPIOE
#define DCMI_RST_Pin GPIO_PIN_14
#define DCMI_RST_GPIO_Port GPIOD
#define DCMI_PWDN_Pin GPIO_PIN_15
#define DCMI_PWDN_GPIO_Port GPIOD
#define DCMI_XCLK_Pin GPIO_PIN_9
#define DCMI_XCLK_GPIO_Port GPIOC
#define USB_CONSIG_Pin GPIO_PIN_10
#define USB_CONSIG_GPIO_Port GPIOC
#define POW_EN_Pin GPIO_PIN_12
#define POW_EN_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOD
#define LED3_Pin GPIO_PIN_2
#define LED3_GPIO_Port GPIOD
#define LED4_Pin GPIO_PIN_3
#define LED4_GPIO_Port GPIOD
#define LED_R_Pin GPIO_PIN_4
#define LED_R_GPIO_Port GPIOD
#define LED_G_Pin GPIO_PIN_5
#define LED_G_GPIO_Port GPIOD
#define LED_B_Pin GPIO_PIN_6
#define LED_B_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
