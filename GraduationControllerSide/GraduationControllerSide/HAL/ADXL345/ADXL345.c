/*
 * ADXL345.c
 *
 *  Created on: 1/2/2024
 *  Author: Hanaa
 *
 */

#include "ADXL345.h"

void Accelerometor_init()
{
	TWI_Init(TWI_PRESCALER,TWI_interrupt_State,TWI_F_SCL,Slave_Address);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_POWER_CTL, Mode);
	clearSettings();
}

// Set Range
void setRange( adxl345_range_t range)
{
	u_int8 value = 0;

	// Update the data rate
	// (&) 0b11110000 (0xF0 - Leave HSB)
	// (|) 0b0000xx?? (range - Set range)
	// (|) 0b00001000 (0x08 - Set Full Res)
	value &= 0xF0;
	value |= range;
	value |= 0x08;
	TWI_ByteWrite(Slave_Address, ADXL345_REG_DATA_FORMAT, value);
}

// Set Data Rate
void setDataRate(adxl345_dataRate_t dataRate)
{
	TWI_ByteWrite(Slave_Address, ADXL345_REG_BW_RATE, dataRate);
}

void clearSettings()
{
	setRange(Range);
	setDataRate(BW_RATE);

	TWI_ByteWrite(Slave_Address, ADXL345_REG_THRESH_TAP, 0x00);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_DUR, 0x00);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_LATENT, 0x00);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_WINDOW, 0x00);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_THRESH_ACT, 0x00);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_THRESH_INACT, 0x00);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_TIME_INACT, 0x00);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_THRESH_FF, 0x00);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_TIME_FF, 0x00);

	u_int8 value;
	TWI_ByteRead(Slave_Address, ADXL345_REG_ACT_INACT_CTL, &value);
	value &= 0b10001000;
	TWI_ByteWrite(Slave_Address, ADXL345_REG_ACT_INACT_CTL, value);

	TWI_ByteRead(Slave_Address, ADXL345_REG_TAP_AXES, &value);
	value &= 0b11111000;
	TWI_ByteWrite(Slave_Address, ADXL345_REG_TAP_AXES, value);
}

void Accelerometor_ReadAxis( volatile ADXL345_Data *Data_ptr)
{
	typedef union
	{
		u_int16 Data;
		struct
		{
			u_int8 LSB;
			u_int8 MSB;
		} Byte;
	} ADXL_DA;

	ADXL_DA X, Y, Z;

	TWI_ByteRead(Slave_Address, ADXL345_REG_DATAX0, &(X.Byte.LSB));
	_delay_ms(1);
	TWI_ByteRead(Slave_Address, ADXL345_REG_DATAX1, &(X.Byte.MSB));
	_delay_ms(1);
	TWI_ByteRead(Slave_Address, ADXL345_REG_DATAY0, &(Y.Byte.LSB));
	_delay_ms(1);
	TWI_ByteRead(Slave_Address, ADXL345_REG_DATAY1, &(Y.Byte.MSB));
	_delay_ms(1);
	TWI_ByteRead(Slave_Address, ADXL345_REG_DATAZ0, &(Z.Byte.LSB));
	_delay_ms(1);
	TWI_ByteRead(Slave_Address, ADXL345_REG_DATAZ1, &(Z.Byte.MSB));
	_delay_ms(1);

	Data_ptr->X_Axis = X.Data;
	Data_ptr->Y_Axis = Y.Data;
	Data_ptr->Z_Axis = Z.Data;
}

// make sure that value between range low-high
float constrain(float amt, float low, float high)
{
	return (amt < low) ? low : ((amt > high) ? high : amt);
}

// th - 0.6, duration - 0.08
void setFreeFallParameters()
{
	u_int8 value = 0;
	TWI_ByteRead(Slave_Address, ADXL345_REG_INT_MAP, &value);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_INT_MAP, value | (FF_INTERRupt_NO << ADXL345_FREE_FALL));
	TWI_ByteRead(Slave_Address, ADXL345_REG_INT_ENABLE, &value);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_INT_ENABLE, value | (1 << ADXL345_FREE_FALL));
	// Set Free Fall Threshold (65.5mg / LSB)
	u_int8 scaled = constrain(FF_Threshold_Val / 0.0625f, 0, 255);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_THRESH_FF, scaled);
	// Set Free Fall Duration (5ms / LSB)
	u_int8 duration = constrain(FF_Duration/ 0.005f, 0, 255);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_TIME_FF, duration);
}

// th - 2
void setActivityParameters()
{
	u_int8 value = 0;
	TWI_ByteRead(Slave_Address, ADXL345_REG_INT_MAP, &value);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_INT_MAP, value | (ACT_INTERRupt_NO << ADXL345_ACTIVITY));
	TWI_ByteRead(Slave_Address, ADXL345_REG_INT_ENABLE, &value);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_INT_ENABLE, value | (1 << ADXL345_ACTIVITY));
	// Set Activity Threshold (62.5mg / LSB)
	u_int8 threshold = constrain(ACT_Threshold_Val / 0.0625f, 0, 255);
	TWI_ByteWrite(Slave_Address, ADXL345_REG_THRESH_ACT, threshold);
	// Set Activity Axis
	TWI_ByteWrite(Slave_Address, ADXL345_REG_ACT_INACT_CTL,ACT_AXIS);
}
