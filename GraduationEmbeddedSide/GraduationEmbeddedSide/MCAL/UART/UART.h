#ifndef UART_H_
#define UART_H_
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BITMATH.h"
#include "UART_Registers.h"
#include "UART_Cfg.h"
#define F_CPU 16000000UL

void UART0_Init(void);
void UART1_Init(void);

void UART0_Transmit(u_int8 Data);
void UART1_Transmit(u_int8 Data);

void UART0_TransmitString(u_int8 * String);
void UART1_TransmitString(u_int8 * String);

void UART0_SendAT(u_int8* String);

u_int8 UART0_Receive(void);
u_int8 UART1_Receive(void);

#endif /* UART_H_ */