#include "TWI.h"

void TWI_Init(TWI_Prescaler Prescale , TWI_interruptState int_state , u_int32 F_SCL , u_int8 Address)
{
	TWAR = Address<<1;
	 /*  Calculating Bit Rate: */
	switch (Prescale)
	{
		case TWI_PRESCALE1:
			TWBR = (u_int8) (((float)F_CPU/(2.0*F_SCL)) -8);
			break;
		case TWI_PRESCALE4:
			TWBR = (u_int8) (((float)F_CPU/(8.0*F_SCL)) -2);
			break;
		case TWI_PRESCALE16:
			TWBR = (u_int8) (((float)F_CPU/(32*F_SCL)) -0.5);
								break;
		case TWI_PRESCALE64:
			TWBR = (u_int8) (((float)F_CPU/(128*F_SCL)) -0.125);
			break;
		default:
			break;
	}
	TWSR |= (Prescale & 0x03);
	TWCR |= (1<<TWEN) | (int_state & 0x01) ;
}

void TWI_Start(void)
{
	 
	/* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
	
	TWCR &= 0X07;           //save first 3 bits Int_En and I2C_EN
	TWCR |= (1<<TWINT) | (1<<TWSTA);  //TWINT flag = 1 to start send start condition
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
   while(ISBETCLEAR(TWCR,TWINT));
}

void TWI_Stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR &= 0x07;
	
    TWCR |=  (1<<TWINT) | (1<<TWSTO);
 
}

void TWI_Write(u_int8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
	TWCR &= 0X07;
	
   TWCR |=(1<<TWINT);
   
   /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
   while(ISBETCLEAR(TWCR,TWINT));
}

u_int8 TWI_Read_With_ACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
	TWCR &= 0X07;
    TWCR |= (1<<TWINT) | (1<<TWEA);
	    
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(ISBETCLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

u_int8 TWI_Read_With_NACK(void)
{

	TWCR &= 0X07;
	TWCR |= (1<<TWINT);
	
	
	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(ISBETCLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

u_int8 TWI_Get_Status(void)
{
   
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    return (TWSR & 0xF8);
}


TWI_States TWI_ByteWrite(u_int8 SL_Address,u_int8 Reg_Address ,u_int8 Data )
{
	TWI_Start();
	while (TWI_Get_Status() != TW_START); // 0x08 
	
	TWI_Write((SL_Address<<1));
	while (TWI_Get_Status() != TW_MT_SLA_W_ACK);
	
	TWI_Write(Reg_Address);
	while (TWI_Get_Status() != TW_MT_DATA_ACK);
	
	TWI_Write(Data);
	while (TWI_Get_Status() != TW_MT_DATA_ACK);
	
	TWI_Stop(); // Send A stop  // Release The Clock Bus 
	return 0;
}

 
TWI_States TWI_ByteRead(u_int8 SL_Address , u_int8 Reg_Address , u_int8 * DataRcv)
{
	
	TWI_Start();
	while (TWI_Get_Status() != TW_START);
	
	TWI_Write((SL_Address<<1));
	while (TWI_Get_Status() != TW_MT_SLA_W_ACK);
	
	TWI_Write(Reg_Address);
	while (TWI_Get_Status() != TW_MT_DATA_ACK);
	
	TWI_Start(); //rep start
	while (TWI_Get_Status() != TW_REP_START);
	
	TWI_Write((SL_Address<<1) | READ);
	while (TWI_Get_Status() != TW_MT_SLA_R_ACK);
	
	*DataRcv=TWI_Read_With_NACK();
	TWI_Stop();

	return 0;		
}
 