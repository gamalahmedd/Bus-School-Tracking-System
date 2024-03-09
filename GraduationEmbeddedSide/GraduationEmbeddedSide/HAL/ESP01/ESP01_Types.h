#ifndef ESP01_TYPES_H_
#define ESP01_TYPES_H_
#include "../../LIB/STD_TYPES.h"

// CR+LF
#define CR 0x0D
#define LF 0x0A

//Respone Variables
#define OK 1
#define Ready 2
#define no_change 3
#define send_ready 4
#define NO_AP 5
#define Connected 6

//ESP Variables
u_int8 rx_buff[500];
u_int8 data_ready;
u_int16 data_len;
u_int8 temp;
u_int8 APIP[20];
u_int8 APMAC[20];
u_int8 STAIP[20];
u_int8 STAMAC[20];

#endif