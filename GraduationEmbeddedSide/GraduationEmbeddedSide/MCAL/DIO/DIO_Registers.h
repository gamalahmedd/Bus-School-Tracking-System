#ifndef DIO_REGISTERS_H_
#define DIO_REGISTERS_H_
#include "../../LIB/STD_TYPES.h"
/*==========(PORTA Registers)==========*/
#define PORTA_Register (*(volatile u_int8*)0x3B)
#define DDRA_Register (*(volatile u_int8*)0x3A)
#define PINA_Register (*(volatile u_int8*)0x39)
/*==========(PORTB Registers)==========*/
#define PORTB_Register (*(volatile u_int8*)0x38)
#define DDRB_Register (*(volatile u_int8*)0x37)
#define PINB_Register (*(volatile u_int8*)0x36)
/*==========(PORTC Registers)==========*/
#define PORTC_Register (*(volatile u_int8*)0x35)
#define DDRC_Register (*(volatile u_int8*)0x34)
#define PINC_Register (*(volatile u_int8*)0x33)
/*==========(PORTD Registers)==========*/
#define PORTD_Register (*(volatile u_int8*)0x32)
#define DDRD_Register (*(volatile u_int8*)0x31)
#define PIND_Register (*(volatile u_int8*)0x30)
/*==========(PORTE Registers)==========*/
#define PORTE_Register (*(volatile u_int8*)0x23)
#define DDRE_Register (*(volatile u_int8*)0x22)
#define PINE_Register (*(volatile u_int8*)0x21)
/*==========(PORTF Registers)==========*/
#define PORTF_Register (*(volatile u_int8*)0x62)
#define DDRF_Register (*(volatile u_int8*)0x61)
#define PINF_Register (*(volatile u_int8*)0x20)
/*==========(PORTG Registers)==========*/
#define PORTG_Register (*(volatile u_int8*)0x65)
#define DDRG_Register (*(volatile u_int8*)0x64)
#define PING_Register (*(volatile u_int8*)0x63)
/*===============(END)===============*/

#endif