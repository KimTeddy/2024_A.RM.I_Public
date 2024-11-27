#pragma once
#include <windows.h>

#define UART_MAX_PORT_NUM 40
#define UART_DECLINE_ERROR 1
void ErrorHandler(const char* msg);
void UART_init(bool error_handle = 0);
int UART_read(char destination[]);
void UART_end();