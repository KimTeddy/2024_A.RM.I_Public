/*
 * armi_uart.h
 *
 *  Created on: Nov 15, 2024
 *      Author: KimTeddy
 */

#ifndef ARMI_UART_H_
#define ARMI_UART_H_

#include "main.h"
#include "usart.h"

extern const uint8_t str_hello[20];

void vprint(const char *fmt, va_list argp);
void my_printf(const char *fmt, ...); // custom printf() function

#endif /* ARMI_UART_H_ */
