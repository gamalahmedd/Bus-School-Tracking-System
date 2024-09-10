#ifndef GPS_TYPES_H_
#define GPS_TYPES_H_
#include "../../MCAL/UART/UART.h"
#include "../../LIB/Clock.h"
#include "../../LIB/String_Find.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GIE/GIE.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#define Buffer_Size 150
#define degrees_buffer_size 20

char Latitude_Buffer[15];
char Longitude_Buffer[15];
char Time_Buffer[15];
char Altitude_Buffer[8];
char degrees_buffer[degrees_buffer_size];
char GGA_Buffer[Buffer_Size];
u_int8 GGA_Pointers[20];
char GGA_CODE[3];
u_int8 received_char;

volatile u_int16 GGA_Index, CommaCounter;


#endif