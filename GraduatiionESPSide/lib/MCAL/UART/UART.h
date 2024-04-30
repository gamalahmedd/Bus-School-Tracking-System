#ifndef UART_H_
#define UART_H_
#include <Arduino.h>

void UART_Init();
void UART_Transmit(char* data);
char UART_Receive();
char UART_isAvailable();
void UART_Flush();
#endif