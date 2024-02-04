#ifndef TWI_H_
#define TWI_H_
#include "TWI_Cfg.h"

void TWI_MasterInit(u_int8 Address, u_int32 F_TWI, TWI_Prescaler_Value Prescaler);
void TWI_SlaveInit(u_int8 Address);
void TWI_MasterStart(void);
void TWI_MasterSendAddress(u_int8 SLA_RW);
void TWI_MasterTransmitData(u_int8 data);
u_int8 TWI_MasterReceiveData(void);
void TWI_MasterSendACK(void);
void TWI_MasterSendNACK(void);
void TWI_MasterStop(void);
void TWI_SlaveReceiveACK(void);
void TWI_SlaveSendACK(void);
u_int8 TWI_Status(void);

#endif