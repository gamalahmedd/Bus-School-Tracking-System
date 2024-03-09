#ifndef UART_TYPES_H_
#define UART_TYPES_H_

typedef enum
{
	MPCM = 0,
	U2X,
	UPE,
	DOR,
	FE,
	UDRE,
	TXC,
	RXC,
}UCSRnA_Bits;

typedef enum
{
	TXB8 = 0,
	RXB8,
	UCSZ2,
	TXEN,
	RXEN,
	UDRIE,
	TXCIE,
	RXCIE,
}UCSRnB_Bits;

typedef enum
{
	UCPOL = 0,
	UCSZ0,
	UCSZ1,
	USBS,
	UPM0,
	UPM1,
	UMSEL,
}UCSRnC_Bits;

typedef enum
{
	UART_Asynchronous_Operration=0,
	UART_Synchronous_Operration
}UART_Operation_Mode_Types;

typedef enum
{
	UART_Parity_Disable,
	UART_Parity_Even=2,
	UART_Parity_Odd=3
}UART_Parity_Mode_Types;

typedef enum
{
	UART_1_StopBit=0,
	UART_2_StopBit
}UART_Stop_Bit_Mode_Types;

typedef enum
{
	UART_CharSize_5Bit=0,
	UART_CharSize_6Bit,
	UART_CharSize_7Bit,
	UART_CharSize_8Bit,
	UART_CharSize_9Bit
}UART_Character_Size_Mode_Types;

typedef enum
{
	UART_TX_Disable=0,
	UART_TX_Enable
}UART_TX_Mode;

typedef enum
{
	UART_TX_Interrupt_Disable=0,
	UART_TX_Interrupt_Enable
}UART_TX_Interrupt_State;

typedef enum
{
	UART_RX_Disable=0,
	UART_RX_Enable
}UART_RX_Mode;

typedef enum
{
	UART_RX_Interrupt_Disable=0,
	UART_RX_Interrupt_Enable
}UART_RX_Interrupt_State;

typedef enum
{
	UART_DoubleSpeed_Disable=0,
	UART_DoubleSpeed_Enable
}UART_DoubleSpeed_Mode;

typedef enum
{
	UART_BaudRate_2400=2400,
	UART_BaudRate_4800=4800,
	UART_BaudRate_9600=9600,
	UART_BaudRate_14_4K=14400,
	UART_BaudRate_19_2K=19200,
	UART_BaudRate_28_8K=28800,
	UART_BaudRate_38_4K=38400,
	UART_BaudRate_57_6K=57600,
	UART_BaudRate_76_8K=76800,
	UART_BaudRate_115_2K=115200,
	UART_BaudRate_230_4K=230400,
	UART_BaudRate_250K=250000
}UART_BaudRate_Types;


#endif