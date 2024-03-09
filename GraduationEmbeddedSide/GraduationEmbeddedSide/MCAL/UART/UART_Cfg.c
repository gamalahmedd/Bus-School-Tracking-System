#include "UART_Cfg.h"

UART_Config UART0_Cfg = 
{
	UART_Asynchronous_Operration,
	UART_Parity_Disable,
	UART_1_StopBit,
	UART_CharSize_8Bit,
	UART_TX_Enable,
	UART_TX_Interrupt_Disable,
	UART_RX_Enable,
	UART_RX_Interrupt_Disable,
	UART_DoubleSpeed_Disable,
	UART_BaudRate_9600
};

UART_Config UART1_Cfg =
{
	UART_Asynchronous_Operration,
	UART_Parity_Disable,
	UART_1_StopBit,
	UART_CharSize_8Bit,
	UART_TX_Enable,
	UART_TX_Interrupt_Disable,
	UART_RX_Enable,
	UART_RX_Interrupt_Enable,
	UART_DoubleSpeed_Disable,
	UART_BaudRate_9600
};