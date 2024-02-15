#ifndef EXTI_REGISTERS_H_
#define EXTI_REGISTERS_H_
#include "../../LIB/STD_TYPES.h"

#define EICRA_Register (*(volatile u_int8*)0x6A)
#define EICRB_Register (*(volatile u_int8*)0x5A)
#define EIMSK_Register (*(volatile u_int8*)0x59)
#define EIFR_Register (*(volatile u_int8*)0x58)

#endif