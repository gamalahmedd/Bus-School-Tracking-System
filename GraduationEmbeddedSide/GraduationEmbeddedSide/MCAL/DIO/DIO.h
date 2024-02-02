#ifndef DIO_H_
#define DIO_H_
#include "DIO_Cfg.h"
/*====================(DIO Functions Prototype)====================*/
void DIO_Init(void);
void DIO_WriteChannel(DIO_ChannelTypes ChannelID , STD_LevelTypes Level);
STD_LevelTypes DIO_ReadChannel(DIO_ChannelTypes ChannelID);
void DIO_ConfigChannel(DIO_ChannelTypes ChannelID , DIO_DirectionTypes Direction);
void DIO_ConfigPullUp(DIO_ChannelTypes ChannelID , DIO_PullUpType PullUp);
void DIO_ToggleChannel(DIO_ChannelTypes ChannelID);

// PortValue written in binary form  0B00000000
void DIO_WritePort(DIO_PortTypes PortID,u_int8 PortValue);
u_int8 DIO_ReadPort(DIO_PortTypes PortID);
void DIO_WriteLowNibble(DIO_PortTypes PortID, u_int8 NibbleValue);
void DIO_WriteHighNibble(DIO_PortTypes PortID, u_int8 NibbleValue);

#endif