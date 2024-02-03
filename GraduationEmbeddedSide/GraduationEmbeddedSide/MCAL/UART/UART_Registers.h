#ifndef UART_REGISTERS_H_
#define UART_REGISTERS_H_
#include "../../LIB/STD_TYPES.h"
/*=============UART0============*/
#define UCSR0C_Register (*(volatile u_int8*)0x95)
#define UCSR0B_Register (*(volatile u_int8*)0x2A)
#define UCSR0A_Register (*(volatile u_int8*)0x2B)
#define UDR0_Register (*(volatile u_int8*)0x2C)
#define UBRR0L_Register (*(volatile u_int8*)0x29)
#define UBRR0H_Register (*(volatile u_int8*)0x90)
/*=============UART1============*/
#define UCSR1C_Register (*(volatile u_int8*)0x9D)
#define UCSR1B_Register (*(volatile u_int8*)0x9A)
#define UCSR1A_Register (*(volatile u_int8*)0x9B)
#define UDR1_Register (*(volatile u_int8*)0x9C)
#define UBRR1L_Register (*(volatile u_int8*)0x99)
#define UBRR1H_Register (*(volatile u_int8*)0x98)
/*=============END============*/
#endif