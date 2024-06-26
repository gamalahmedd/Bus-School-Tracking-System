#ifndef TWI_H_
#define TWI_H_

#include "../../LIB/Clock.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BITMATH.h"
#include "../../MCAL/DIO/DIO.h"
#include "TWI_Registers.h"
#include "TWI_Types.h"
#include "TWI_Config.h"

void TWI_Init(TWI_Prescaler Prescale,TWI_interruptState int_state,u_int32 F_SCL,u_int8 TWI_Address);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(u_int8 data);
u_int8 TWI_Read_With_ACK(void); //read with send Ack
u_int8 TWI_Read_With_NACK(void); //read without send Ack
u_int8 TWI_Get_Status(void);
TWI_States TWI_ByteWrite(u_int8 SL_Address, u_int8 Reg_Address ,u_int8 Data);
TWI_States TWI_ByteRead(u_int8 SL_Address , u_int8 Reg_Address , u_int8 * DataRcv);

#endif