#include "LCD.h"

void LCD_Init()
{
	DIO_ConfigPort(LCD_Data_Port, 0xFF);
	DIO_ConfigChannel(LCD_EN, OUTPUT);
	DIO_ConfigChannel(LCD_RS, OUTPUT);
	DIO_ConfigChannel(LCD_RW, OUTPUT);
	_delay_ms(200);
	DIO_WriteChannel(LCD_RW, STD_LOW);
	switch(LCD_CFG.Mode)
	{
		case Eight_Bit_Mode:
		{
			LCD_SendCmd(LCD_CFG.Mode);
			_delay_ms(1);
			LCD_SendCmd(LCD_CFG.Display_Control);
			_delay_ms(1);
			LCD_SendCmd(LCD_Clear_Screen);
			_delay_ms(10);
			LCD_SendCmd(LCD_CFG.Entry_Mode);
			_delay_ms(1);
		}
		case Four_Bit_Mode:
		{
			LCD_SendCmd(LCD_Return_Home);
			_delay_ms(10);
			LCD_SendCmd(LCD_CFG.Mode);
			_delay_ms(1);
			LCD_SendCmd(LCD_CFG.Display_Control);
			_delay_ms(1);
			LCD_SendCmd(LCD_Clear_Screen);
			_delay_ms(10);
			LCD_SendCmd(LCD_CFG.Entry_Mode);
			_delay_ms(1);
		}
	}
}

void Enable()
{
	DIO_WriteChannel(LCD_EN, STD_HIGH);
	_delay_ms(2);
	DIO_WriteChannel(LCD_EN, STD_LOW);
	_delay_ms(2);
}

void LCD_SendCmd(u_int8 Cmd)
{
	switch(LCD_CFG.Mode)
	{
		case Eight_Bit_Mode:
		{
			DIO_WriteChannel(LCD_RS, STD_LOW);
			DIO_WritePort(LCD_Data_Port, Cmd);
			Enable();
			_delay_ms(1);
			break;
		}
		case Four_Bit_Mode:
		{
			DIO_WriteChannel(LCD_RS, STD_LOW);
			DIO_WriteHighNibble(LCD_Data_Port, Cmd >> 4);
			Enable();
			DIO_WriteHighNibble(LCD_Data_Port, Cmd);
			Enable();
			_delay_ms(1);
			break;
		}
	}
}

void LCD_SendChar(u_int8 Data, u_int8 row, u_int8 column)
{
	u_int8 cmd = 0;
	if(row < 1 || row > 4 || column < 1 || column > 16)
	{
		cmd = 0x00;
	}
	else
	{
		switch(row)
		{
			case 1:
			cmd = 0x80 + column - 1;
			break;
			case 2:
			cmd = 0xC0 + column - 1;
			break;
			case 3:
			cmd = 0x90 + column - 1;
			break;
			case 4:
			cmd = 0xD0 + column - 1;
			break;
		}
	}
	LCD_SendCmd(cmd);
	
	switch(LCD_CFG.Mode)
	{
		case Eight_Bit_Mode:
		{
			DIO_WriteChannel(LCD_RS, STD_HIGH);
			DIO_WritePort(LCD_Data_Port, Data);
			Enable();
			_delay_ms(1);
			break;
		}
		case Four_Bit_Mode:
		{
			DIO_WriteChannel(LCD_RS, STD_HIGH);
			DIO_WriteHighNibble(LCD_Data_Port, Data >> 4);
			Enable();
			DIO_WriteHighNibble(LCD_Data_Port, Data);
			Enable();
			_delay_ms(1);
			break;
		}
	}
}

void LCD_SendString(u_int8* String, u_int8 row, u_int8 column)
{
	while((*String) != 0)
	{
		LCD_SendChar(*String, row, column);
		column++;
		String++;
	}
}

void LCD_ClearScreen()
{
	LCD_SendCmd(LCD_Clear_Screen);
}

void LCD_Custom_Char(u_int8 Location, u_int8* Character)
{
	if(Location < 8)
	{
		LCD_SendCmd((0x40 + (Location * 8)));
		u_int8 i;
		for(i = 0; i < 8; i++)
			LCD_SendChar(Character[i], 0, 0);
	}
}