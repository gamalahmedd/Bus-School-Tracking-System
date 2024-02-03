#include "UART.h"
#include "../../LIB/Clock.h"


void UART0_Init(void)
{
	UCSR0C_Register |= (UART0_Cfg.Operation_Mode << UMSEL);
	UCSR0C_Register |= (UART0_Cfg.Parity_Mode << UPM0);
	UCSR0C_Register |= (UART0_Cfg.Stop_Bit_Mode << USBS);
	UCSR0B_Register |= (UART0_Cfg.TX_Mode << TXEN);
	UCSR0B_Register |= (UART0_Cfg.RX_Mode << RXEN);
	u_int16 UBRR0 = 0;
	switch(UART0_Cfg.DoubleSpeed_Mode)
	{
		case UART_DoubleSpeed_Disable:
			ClearBit(UCSR0A_Register, U2X);
			UBRR0 = ((F_CPU/(16UL*UART0_Cfg.BaudRate_Value)))-1;
			break;
		case UART_DoubleSpeed_Enable:
			SetBit(UCSR0A_Register, U2X);
			UBRR0 = ((F_CPU/(8UL*UART0_Cfg.BaudRate_Value)))-1;
			break;
	}
	UBRR0H_Register = (u_int8) (UBRR0 >> 8);
	UBRR0L_Register = (u_int8) UBRR0;
	if(UART0_Cfg.Character_Size_Mode == UART_CharSize_9Bit)
	{
		SetBit(UCSR0C_Register, UCSZ0);
		SetBit(UCSR0C_Register, UCSZ1);
		SetBit(UCSR0B_Register, UCSZ2);
	}
	else
	{
		UCSR0C_Register |= (UART0_Cfg.Character_Size_Mode << UCSZ0);
	}
}

void UART1_Init(void)
{
	UCSR1C_Register |= (UART1_Cfg.Operation_Mode << UMSEL);
	UCSR1C_Register |= (UART1_Cfg.Parity_Mode << UPM0);
	UCSR1C_Register |= (UART1_Cfg.Stop_Bit_Mode << USBS);
	UCSR1B_Register |= (UART0_Cfg.TX_Mode << TXEN);
	UCSR1B_Register |= (UART0_Cfg.RX_Mode << RXEN);
	u_int16 UBRR1 = 0;
	switch(UART1_Cfg.DoubleSpeed_Mode)
	{
		case UART_DoubleSpeed_Disable:
		ClearBit(UCSR1A_Register, U2X);
		UBRR1 = ((F_CPU/(16UL*UART1_Cfg.BaudRate_Value)))-1;
		break;
		case UART_DoubleSpeed_Enable:
		SetBit(UCSR1A_Register, U2X);
		UBRR1 = ((F_CPU/(8UL*UART1_Cfg.BaudRate_Value)))-1;
		break;
	}
	UBRR1H_Register = (u_int8) (UBRR1 >> 8);
	UBRR1L_Register = (u_int8) UBRR1;
	if(UART1_Cfg.Character_Size_Mode == UART_CharSize_9Bit)
	{
		SetBit(UCSR1C_Register, UCSZ0);
		SetBit(UCSR1C_Register, UCSZ1);
		SetBit(UCSR1B_Register, UCSZ2);
	}
	else
	{
		UCSR1C_Register |= (UART1_Cfg.Character_Size_Mode << UCSZ0);
	}
}

void UART0_Transmit(u_int8 Data)
{
	while(ReadBit(UCSR0A_Register, UDRE) == 0);
	UDR0_Register = Data;
}

void UART1_Transmit(u_int8 Data)
{
	while(ReadBit(UCSR1A_Register, UDRE) == 0);
	UDR1_Register = Data;
}

void UART0_TransmitString(u_int8 * String)
{
	while(String != 0)
	{
		UART0_Transmit(*String);
		String++;
		_delay_ms(50);
	}
}

void UART1_TransmitString(u_int8 * String)
{
	while(String != 0)
	{
		UART1_Transmit(*String);
		String++;
		_delay_ms(50);
	}
}

u_int8 UART0_Receive(void)
{
	u_int8 data = 0;
	while(ReadBit(UCSR0A_Register, RXC) == 0);
	data = UDR0_Register;
	return data;
}

u_int8 UART1_Receive(void)
{
	u_int8 data = 0;
	while(ReadBit(UCSR1A_Register, RXC) == 0);
	data = UDR1_Register;
	return data;
}