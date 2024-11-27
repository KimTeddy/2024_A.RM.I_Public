/*
 * armi_uart.c
 *
 *  Created on: Nov 15, 2024
 *      Author: KimTeddy
 */

#include "armi_uart.h"

#ifdef DEBUG
const uint8_t str_hello[20] = "\n\r<Hello A.RM.I>\n\r";
#endif

//UART
void vprint(const char *fmt, va_list argp) {
	char string_v[65535];
	if (0 < vsprintf(string_v, fmt, argp)) // build string
			{
		//armi_led(4, 1);
		HAL_UART_Transmit(&huart1, (uint8_t*) string_v, strlen(string_v),
				0xffffff); // send message via UART
		//armi_led(4, 0);
	}
}

void my_printf(const char *fmt, ...) // custom printf() function
{
	va_list argp;
	va_start(argp, fmt);
	vprint(fmt, argp);
	va_end(argp);
}
