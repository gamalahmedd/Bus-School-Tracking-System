#ifndef GPS_TYPES_H_
#define GPS_TYPES_H_
#include "../../MCAL/UART/UART.h"
#include "../../LIB/Clock.h"
#include "../../LIB/String_Find.h"
#include "../../LIB/STD_TYPES.h"
#include <avr/interrupt.h>

u_int8 gps_buff_len;
u_int8 gps_buff[500];



#endif