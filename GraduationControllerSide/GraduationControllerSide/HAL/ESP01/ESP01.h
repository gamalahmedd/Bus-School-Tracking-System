#ifndef ESP01_H_
#define ESP01_H_
#include "UART.h"
#include "String_Find.h"
#include "ESP01_Types.h"
#include <string.h>

void ESP01_Init();
u_int8 ESP01_CheckConnection();
void ESP01_ResetBuffer();

#endif