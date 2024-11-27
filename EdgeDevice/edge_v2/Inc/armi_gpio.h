/*
 * armi_gpio.h
 *
 *  Created on: Nov 15, 2024
 *      Author: KimTeddy
 */

#ifndef INC_ARMI_GPIO_H_
#define INC_ARMI_GPIO_H_

#include "main.h"
#include "armi_relay.h"

#define ARMI_2_1

#define R 5
#define G 6
#define B 7

extern uint8_t armi_devnum;

void armi_led(uint8_t num, bool onoff);
void armi_led_blink(uint8_t num, uint32_t delay);
void armi_led_test();

uint8_t armi_dipsw_devnum();
uint8_t armi_get_devnum();

#endif /* INC_ARMI_GPIO_H_ */
