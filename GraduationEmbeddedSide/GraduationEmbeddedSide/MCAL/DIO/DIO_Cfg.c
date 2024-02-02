#include "DIO_Cfg.h"

DIO_PinConfig PinConfig[]=
{
	{OUTPUT, DIO_PortA, DIO_ChannelA0, EMPTY},
	{OUTPUT, DIO_PortB, DIO_ChannelB0, EMPTY},
	{INPUT, DIO_PortC, DIO_ChannelC0, EMPTY},
};

const u_int8 countPinsConfigured = sizeof(PinConfig) / sizeof(PinConfig[0]);