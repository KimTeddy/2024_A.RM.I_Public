/*
 * armi_gpio.c
 *
 *  Created on: Nov 15, 2024
 *      Author: KimTeddy
 */

#include "armi_gpio.h"

uint8_t armi_devnum = 0;

#ifdef ARMI_2_1
void armi_led(uint8_t num, bool onoff) {
	GPIO_TypeDef *led_port = GPIOD;
	uint16_t led_pin = 0;
	switch (num) {
	case 1:
		led_pin = GPIO_PIN_0;
		break;
	case 2:
		led_pin = GPIO_PIN_1;
		break;
	case 3:
		led_pin = GPIO_PIN_2;
		break;
	case 4:
		led_pin = GPIO_PIN_3;
		break;
	case 5:
		led_pin = GPIO_PIN_4;
		break;
	case 6:
		led_pin = GPIO_PIN_5;
		break;
	case 7:
		led_pin = GPIO_PIN_6;
		break;
	default:
		return;
	}
	HAL_GPIO_WritePin(led_port, led_pin, onoff);
}

void armi_led_blink(uint8_t num, uint32_t delay) {
	GPIO_TypeDef *led_port = GPIOD;
	uint16_t led_pin = 0;
	switch (num) {
	case 1:
		led_pin = GPIO_PIN_0;
		break;
	case 2:
		led_pin = GPIO_PIN_1;
		break;
	case 3:
		led_pin = GPIO_PIN_2;
		break;
	case 4:
		led_pin = GPIO_PIN_3;
		break;
	case 5:
		led_pin = GPIO_PIN_4;
		break;
	case 6:
		led_pin = GPIO_PIN_5;
		break;
	case 7:
		led_pin = GPIO_PIN_6;
		break;
	default:
		return;
	}
	HAL_GPIO_WritePin(led_port, led_pin, GPIO_PIN_SET);
	HAL_Delay(delay);
	HAL_GPIO_WritePin(led_port, led_pin, GPIO_PIN_RESET);
}
#else
void armi_led(uint8_t num, bool onoff) {
	GPIO_TypeDef *led_port = GPIOD;
	uint16_t led_pin = 0;
	if (num > 4)
		led_port = GPIOB;
	switch (num) {
	case 1:
		led_pin = GPIO_PIN_4;
		break;
	case 2:
		led_pin = GPIO_PIN_5;
		break;
	case 3:
		led_pin = GPIO_PIN_6;
		break;
	case 4:
		led_pin = GPIO_PIN_7;
		break;
	case 5:
		led_pin = GPIO_PIN_3;
		break;
	case 6:
		led_pin = GPIO_PIN_4;
		break;
	case 7:
		led_pin = GPIO_PIN_5;
		break;
	default:
		return;
	}
	HAL_GPIO_WritePin(led_port, led_pin, onoff);
}

void armi_led_blink(uint8_t num, uint32_t delay) {
	GPIO_TypeDef *led_port = GPIOD;
	uint16_t led_pin = 0;
	if (num > 4)
		led_port = GPIOB;
	switch (num) {
	case 1:
		led_pin = GPIO_PIN_4;
		break;
	case 2:
		led_pin = GPIO_PIN_5;
		break;
	case 3:
		led_pin = GPIO_PIN_6;
		break;
	case 4:
		led_pin = GPIO_PIN_7;
		break;
	case 5:
		led_pin = GPIO_PIN_3;
		break;
	case 6:
		led_pin = GPIO_PIN_4;
		break;
	case 7:
		led_pin = GPIO_PIN_5;
		break;
	default:
		return;
	}
	HAL_GPIO_WritePin(led_port, led_pin, GPIO_PIN_SET);
	HAL_Delay(delay);
	HAL_GPIO_WritePin(led_port, led_pin, GPIO_PIN_RESET);
}
#endif
void armi_led_test(){
	armi_led(1, 1);
	armi_led(R, 1);
	HAL_Delay(100);

	armi_led(1, 0);
	armi_led(2, 1);
	armi_led(R, 0);
	armi_led(G, 1);
	HAL_Delay(100);

	armi_led(2, 0);
	armi_led(3, 1);
	armi_led(G, 0);
	armi_led(B, 1);
	HAL_Delay(100);

	armi_led(3, 0);
	armi_led(4, 1);
	armi_led(R, 1);
	armi_led(G, 1);
	HAL_Delay(100);

	armi_led(1, 0);
	armi_led(2, 0);
	armi_led(3, 0);
	armi_led(4, 0);
	armi_led(R, 0);
	armi_led(G, 0);
	armi_led(B, 0);
}

uint8_t armi_dipsw_devnum() {
	// Clear PUPDR bits for PA0 ~ PA3 to 00 (no pull-up/pull-down initially)
	GPIOA->PUPDR &= ~(0x3 << (0 * 2));  // Clear PA0
	GPIOA->PUPDR &= ~(0x3 << (1 * 2));  // Clear PA1
	GPIOA->PUPDR &= ~(0x3 << (2 * 2));  // Clear PA2
	GPIOA->PUPDR &= ~(0x3 << (3 * 2));  // Clear PA3

	// Set PUPDR bits to 01 for PA0 ~ PA3 to enable pull-up
	GPIOA->PUPDR |= (0x1 << (0 * 2));   // Enable pull-up for PA0
	GPIOA->PUPDR |= (0x1 << (1 * 2));   // Enable pull-up for PA1
	GPIOA->PUPDR |= (0x1 << (2 * 2));   // Enable pull-up for PA2
	GPIOA->PUPDR |= (0x1 << (3 * 2));   // Enable pull-up for PA3

	HAL_Delay(50);

	uint8_t addr0State = HAL_GPIO_ReadPin(ADDR0_GPIO_Port, ADDR0_Pin);
	uint8_t addr1State = HAL_GPIO_ReadPin(ADDR1_GPIO_Port, ADDR1_Pin);
	uint8_t addr2State = HAL_GPIO_ReadPin(ADDR2_GPIO_Port, ADDR2_Pin);
	uint8_t addr3State = HAL_GPIO_ReadPin(ADDR3_GPIO_Port, ADDR3_Pin);

	// Set PUPDR bits for PA0 ~ PA3 to 00 (disable pull-up/pull-down)
	GPIOA->PUPDR &= ~(0x3 << (0 * 2));  // Disable pull-up for PA0
	GPIOA->PUPDR &= ~(0x3 << (1 * 2));  // Disable pull-up for PA1
	GPIOA->PUPDR &= ~(0x3 << (2 * 2));  // Disable pull-up for PA2
	GPIOA->PUPDR &= ~(0x3 << (3 * 2));  // Disable pull-up for PA3

	return addr3State * 8 + addr2State * 4 + addr1State * 2 + addr0State;
}

uint8_t armi_get_devnum(){
	armi_devnum = armi_dipsw_devnum();

	addr_dev[0] = armi_devnum;

	if (armi_devnum & 1)
		armi_led(1, 1);
	if (armi_devnum >> 1 & 1)
		armi_led(2, 1);
	if (armi_devnum >> 2 & 1)
		armi_led(3, 1);
	if (armi_devnum >> 3 & 1)
		armi_led(4, 1);
	if (armi_devnum > 15) {
		armi_led(1, 1);
		armi_led(2, 1);
		armi_led(3, 1);
		armi_led(4, 1);
	}
	HAL_Delay(1000);
	armi_led(1, 0);
	armi_led(2, 0);
	armi_led(3, 0);
	armi_led(4, 0);

	return armi_devnum;
}
#ifdef ASFD
void armi_led(uint8_t num, bool onoff) {
	GPIO_TypeDef *led_port = 0;
	uint16_t led_pin = 0;
	switch (num) {
	case 1:
		led_port = GPIOC;
		led_pin = GPIO_PIN_7;
		break;
	case 2:
		led_port = GPIOB;
		led_pin = GPIO_PIN_7;
		break;
	case 3:
		led_port = GPIOG;
		led_pin = GPIO_PIN_2;
		break;
	default:
		return;
	}
	HAL_GPIO_WritePin(led_port, led_pin, onoff);
}
#endif
