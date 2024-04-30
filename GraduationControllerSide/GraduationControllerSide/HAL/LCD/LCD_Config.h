#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_
#include "LCD_Types.h"

typedef struct  
{
	LCD_Entry_Mode Entry_Mode;
	LCD_Display_Control Display_Control;
	LCD_Mode Mode;
} LCD_Cfg;

extern LCD_Cfg LCD_CFG;


#endif