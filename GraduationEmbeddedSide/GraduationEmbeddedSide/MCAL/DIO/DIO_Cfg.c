#include "DIO_Cfg.h"

DIO_PinConfig PinConfig[]=
{
	{OUTPUT, DIO_PortA, DIO_ChannelA0, EMPTY},
	{OUTPUT, DIO_PortA, DIO_ChannelA1, EMPTY},
	{OUTPUT, DIO_PortA, DIO_ChannelA2, EMPTY},
	{OUTPUT, DIO_PortA, DIO_ChannelA3, EMPTY},
	{OUTPUT, DIO_PortA, DIO_ChannelA4, EMPTY},
	{OUTPUT, DIO_PortA, DIO_ChannelA5, EMPTY},
	{OUTPUT, DIO_PortA, DIO_ChannelA6, EMPTY},
	{OUTPUT, DIO_PortA, DIO_ChannelA7, EMPTY},
	{OUTPUT, DIO_PortC, DIO_ChannelC0, EMPTY},
	{OUTPUT, DIO_PortC, DIO_ChannelC1, EMPTY},
	{OUTPUT, DIO_PortC, DIO_ChannelC2, EMPTY},
};

const u_int8 countPinsConfigured = sizeof(PinConfig) / sizeof(PinConfig[0]);