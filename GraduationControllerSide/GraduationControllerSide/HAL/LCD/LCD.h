#ifndef LCD_H_
#define LCD_H_
#include "LCD_Config.h"
#include "Clock.h"
#include "DIO.h"
#include <stdio.h>

void LCD_Init(void);
void Enable(void);
void LCD_SetCursor(u_int8 row, u_int8 column);
void LCD_SendCmd(u_int8 Cmd);
void LCD_SendChar(u_int8 Data);
void LCD_SendString(u_int8* String);
void LCD_ClearScreen(void);
void LCD_Custom_Char(u_int8 Location, u_int8* Character);
void LCD_DisplayInt(int data);



#endif