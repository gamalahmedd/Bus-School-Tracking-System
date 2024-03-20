#ifndef ESP01_H_
#define ESP01_H_
#include "ESP01_Types.h"
#include "../../MCAL/UART/UART.h"
#include "../../LIB/String_Find.h"
#include "../../LIB/Clock.h"
#include "../../MCAL/GIE/GIE.h"
#include "../../MCAL/DIO/DIO.h"
#include <string.h>

void ESP01_Init();
void ESP01_Connect_Wifi(u_int8 SSID[], u_int8 Password[]);
u_int8 ESP01_Check_Wifi_Connection();
u_int8 ESP01_ResponseSuccess();
void ESP01_Reset_Buffer();
void ESP01_Reset_Wifi();
void ESP01_GetIP_MAC_Addresses();
void ESP01_Create_TCPServer(u_int8* portNumber);
void ESP01_Check_Request();
u_int16 get_size_Data();


#endif