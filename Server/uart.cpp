#include <stdio.h>
#include "uart.hpp"

HANDLE hSerial;
DCB dcbSerialParams = { 0 };
COMMTIMEOUTS timeouts = { 0 };
//LPCWSTR portName = L"\\\\.\\COM20";

void ErrorHandler(const char* msg) {
    printf("%s. Error: %ld\n", msg, GetLastError());
}

void UART_init(bool error_handle) {
    // COM ��Ʈ ����
    for (int port_num = 1; port_num <= UART_MAX_PORT_NUM; port_num++)
    {
        if (port_num == 7 || port_num == 8) continue;
        wchar_t portName[20];
        swprintf(portName, sizeof(portName) / sizeof(portName[0]), L"\\\\.\\COM%d", port_num);

        hSerial = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (hSerial != INVALID_HANDLE_VALUE) {
            wprintf(L"Port Name: %ls\n", portName);
            break;
        }
        else {//port_num�� UART_MAX_PORT_NUM�ε� else�� ���� ���� ��Ʈ��
            if (port_num == UART_MAX_PORT_NUM) {
                ErrorHandler("No COM Port");
                if (error_handle == 0)exit(1);
            }
        }
    }

    // �ø��� ��Ʈ ����
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        ErrorHandler("Error getting state");
        if (error_handle == 0)exit(1);
    }
    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        ErrorHandler("Error setting state");
        if (error_handle == 0)exit(1);
    }

    // Ÿ�Ӿƿ� ����
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        ErrorHandler("Error setting timeouts");
        if (error_handle == 0)exit(1);
    }
}

//void UART_read() {
//    // ������ �б�
//    char buffer[32];
//    DWORD bytesRead;
//    if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) {
//        buffer[bytesRead] = '\0'; // null-terminate the string
//        printf("Received: %s\n", buffer);
//    }
//    else {
//        ErrorHandler("Error reading from COM port");
//    }
//}
int UART_read(char destination[]) {
    // ������ �б�
    char buffer[500000];
    DWORD bytesRead;
    if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) {

        buffer[bytesRead] = '\0'; // null-terminate the string

        int startIndex = -1;
        int endIndex = -1;
        int destIndex = 0;
        int j = 0;

        // ffd8 ã��
        for (int i = 0; i < sizeof(buffer) - 1; i++) {
            if (buffer[i] == 'f' && buffer[i + 1] == 'f' && buffer[i + 2] == 'd' && buffer[i + 3] == '8') {
                startIndex = i;
                break;
            }
        }

        // ffd9 ã��
        if (startIndex != -1) {
            for (int i = startIndex + 2; i < sizeof(buffer) - 1; i++) {
                if (buffer[i] == 'f' && buffer[i + 1] == 'f' && buffer[i + 2] == 'd' && buffer[i + 3] == '9') {
                    endIndex = i + 3;
                    break;
                }
            }
        }

        // �����͸� ����
        if (startIndex != -1 && endIndex != -1) {
            for (int i = startIndex; i <= endIndex; i++) {
                destination[destIndex++] = buffer[i];
                j++;
            }
        }
        destination[destIndex] = '\0';

        printf("Original: %s\n", buffer);
        printf("processed: %s\n", destination);

        return 0;
    }
    else {
        ErrorHandler("Error reading from COM port");
        return 1;
    }
}
void UART_end() {
    CloseHandle(hSerial);
}