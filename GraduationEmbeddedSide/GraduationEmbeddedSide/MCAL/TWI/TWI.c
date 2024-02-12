#include "TWI.h"

void TWI_MasterInit(u_int8 Address, u_int32 F_TWI, TWI_Prescaler_Value Prescaler)
{
	u_int8 PrescalerValue = 1;
	TWSR_Register |= (Prescaler << TWPS0);
	TWAR_Register = Address;
	switch(Prescaler)
	{
		case TWI_Prescaler_1:
			PrescalerValue = 1;
			break;
		case TWI_Prescaler_4:
			PrescalerValue = 4;
			break;
		case TWI_Prescaler_16:
			PrescalerValue = 16;
			break;
		case TWI_Prescaler_64:
			PrescalerValue = 64;
			break;
	}
	TWBR_Register = (((F_CPU/F_TWI)-16)/(2*(4^PrescalerValue)));
}

void TWI_SlaveInit(u_int8 Address)
{
	TWAR_Register = Address;
}

void TWI_MasterStart(void)
{
	TWCR_Register |= MasterStartCondition;
	while(ReadBit(TWCR_Register, TWINT) == 0);
}

void TWI_MasterSendAddress(u_int8 SLA_RW)
{
	TWDR_Register = SLA_RW;
	TWCR_Register |= MasterSend_DataAddress;
	while(ReadBit(TWCR_Register, TWINT) == 0);
}

void TWI_MasterTransmitData(u_int8 data)
{
	TWDR_Register = data;
	TWCR_Register |= MasterSend_DataAddress;
	while(ReadBit(TWCR_Register, TWINT) == 0);
}

u_int8 TWI_MasterReceiveData(void)
{
	return TWDR_Register;
}

void TWI_MasterSendACK(void)
{
	TWCR_Register |= SendACK;
	while(ReadBit(TWCR_Register, TWINT) == 0);
}

void TWI_MasterSendNACK(void)
{
	TWCR_Register |= SendNACK;
	while(ReadBit(TWCR_Register, TWINT) == 0);
}

void TWI_MasterStop(void)
{
	TWCR_Register |= MasterStopCondition;
}

void TWI_SlaveReceiveACK(void)
{
	TWCR_Register |= ReceiveACK;
	while(ReadBit(TWCR_Register, TWINT) == 0);
}

void TWI_SlaveSendACK(void)
{
	TWCR_Register |= SendACK;
	while(ReadBit(TWCR_Register, TWINT) == 0);
}

u_int8 TWI_Status(void)
{
	u_int8 status;
	status = TWSR_Register & 0xF8;
	return status;
}