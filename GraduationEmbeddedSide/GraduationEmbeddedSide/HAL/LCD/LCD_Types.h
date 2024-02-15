#ifndef LCD_TYPES_H_
#define LCD_TYPES_H_
#include "../../MCAL/DIO/DIO.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BITMATH.h"

#define LCD_RS DIO_ChannelC0
#define LCD_RW DIO_ChannelC1
#define LCD_EN DIO_ChannelC2
#define LCD_Data_Port DIO_PortA

#define LCD_Clear_Screen 0x01
#define LCD_Return_Home 0x02

typedef enum
{
	Cursor_Left = 0x04,
	Cursor_Right = 0x06,
	Display_Right = 0x05,
	Display_Left = 0x07,
} LCD_Entry_Mode;

typedef enum
{
	Display_OFF_Cursor_OFF_Blink_OFF = 0x08,
	Display_OFF_Cursor_OFF_Blink_ON = 0x09,
	Display_OFF_Cursor_ON_Blink_OFF = 0x0A,
	Display_OFF_Cursor_ON_Blink_ON = 0x0B,
	Display_ON_Cursor_OFF_Blink_OFF = 0x0C,
	Display_ON_Cursor_OFF_Blink_ON = 0x0D,
	Display_ON_Cursor_ON_Blink_OFF = 0x0E,
	Display_ON_Cursor_ON_Blink_ON = 0x0F,
} LCD_Display_Control;

typedef enum
{
	Shift_Cursor_Left = 0x10,
	Shift_Cursor_Right = 0x14,
	Shift_Display_Left = 0x18,
	Shift_Display_Right = 0x1C,
} Cursor_Or_Display_Shift;

typedef enum
{
	Four_Bit_Mode = 0x28,
	Eight_Bit_Mode = 0x38,
} LCD_Mode;

#endif