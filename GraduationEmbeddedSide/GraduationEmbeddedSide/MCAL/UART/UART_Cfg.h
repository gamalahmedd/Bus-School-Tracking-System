#ifndef UART_CFG_H_
#define UART_CFG_H_
#include "UART_Types.h"

typedef struct  
{
	UART_Operation_Mode_Types Operation_Mode;
	UART_Parity_Mode_Types Parity_Mode;
	UART_Stop_Bit_Mode_Types Stop_Bit_Mode;
	UART_Character_Size_Mode_Types Character_Size_Mode;
	UART_TX_Mode TX_Mode;
	UART_RX_Mode RX_Mode;
	UART_DoubleSpeed_Mode DoubleSpeed_Mode;
	UART_BaudRate_Types BaudRate_Value;
}UART_Config;

extern UART_Config UART0_Cfg;
extern UART_Config UART1_Cfg;

#endif /* UART_CFG_H_ */