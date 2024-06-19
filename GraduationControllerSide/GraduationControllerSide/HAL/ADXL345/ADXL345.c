/*
 * ADXL345.c
 *
 *  Created on: 1/2/2024
 *  Author: Hanaa
 *
 */

#include "ADXL345.h"

void Accelerometor_init(ADX345_PowerModes Mode, ADXL345_Address EFF_Address)
{
	I2C_ByteWrite(EFF_Address, POWER_CTRL, Mode);
	clearSettings(EFF_Address);
}

// Set Range
void setRange(ADXL345_Address EFF_Address, adxl345_range_t range)
{
	// Get actual value register
	u_int8 value = 0;
	I2C_ByteRead(EFF_Address, ADXL345_REG_DATA_FORMAT, &value);

	// Update the data rate
	// (&) 0b11110000 (0xF0 - Leave HSB)
	// (|) 0b0000xx?? (range - Set range)
	// (|) 0b00001000 (0x08 - Set Full Res)
	value &= 0xF0;
	value |= range;
	value |= 0x08;

	I2C_ByteWrite(EFF_Address, ADXL345_REG_DATA_FORMAT, value);
}

// Set Data Rate
void setDataRate(ADXL345_Address EFF_Address, adxl345_dataRate_t dataRate)
{
	I2C_ByteWrite(EFF_Address, ADXL345_REG_BW_RATE, dataRate);
}

void clearSettings(ADXL345_Address EFF_Address)
{
	setRange(EFF_Address, ADXL345_RANGE_2G);
	setDataRate(EFF_Address, ADXL345_DATARATE_100HZ);

	I2C_ByteWrite(EFF_Address, ADXL345_REG_THRESH_TAP, 0x00);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_DUR, 0x00);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_LATENT, 0x00);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_WINDOW, 0x00);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_THRESH_ACT, 0x00);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_THRESH_INACT, 0x00);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_TIME_INACT, 0x00);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_THRESH_FF, 0x00);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_TIME_FF, 0x00);

	u_int8 value;

	I2C_ByteRead(EFF_Address, ADXL345_REG_ACT_INACT_CTL, &value);
	value &= 0b10001000;
	I2C_ByteWrite(EFF_Address, ADXL345_REG_ACT_INACT_CTL, value);

	I2C_ByteRead(EFF_Address, ADXL345_REG_TAP_AXES, &value);
	value &= 0b11111000;
	I2C_ByteWrite(EFF_Address, ADXL345_REG_TAP_AXES, value);
}

void Accelerometor_ReadAxis(ADXL345_Address EFF_Address, volatile ADXL345_Data *Data_ptr)
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

	I2C_ByteRead(EFF_Address, ACCS_DATAX0, &(X.Byte.LSB));
	_delay_ms(1);
	I2C_ByteRead(EFF_Address, ACCS_DATAX1, &(X.Byte.MSB));
	_delay_ms(1);
	I2C_ByteRead(EFF_Address, ACCS_DATAY0, &(Y.Byte.LSB));
	_delay_ms(1);
	I2C_ByteRead(EFF_Address, ACCS_DATAY1, &(Y.Byte.MSB));
	_delay_ms(1);
	I2C_ByteRead(EFF_Address, ACCS_DATAZ0, &(Z.Byte.LSB));
	_delay_ms(1);
	I2C_ByteRead(EFF_Address, ACCS_DATAZ1, &(Z.Byte.MSB));
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

// Set Free Fall Threshold (65.5mg / LSB)
void setFreeFallThreshold(ADXL345_Address EFF_Address, float threshold)
{
	u_int8 scaled = constrain(threshold / 0.0625f, 0, 255);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_THRESH_FF, scaled);
}

// Set Free Fall Duration (5ms / LSB)
void setFreeFallDuration(ADXL345_Address EFF_Address, float duration)
{
	u_int8 scaled = constrain(duration / 0.005f, 0, 255);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_TIME_FF, scaled);
}

// Set Activity Threshold (62.5mg / LSB)
void setActivityThreshold(ADXL345_Address EFF_Address, float threshold)
{
	u_int8 scaled = constrain(threshold / 0.0625f, 0, 255);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_THRESH_ACT, scaled);
}

// set activity mode in y only - dc mode   0b 0010 0000
void setYActivity(ADXL345_Address EFF_Address)
{
	I2C_ByteWrite(EFF_Address, ADXL345_REG_ACT_INACT_CTL, 0x20);
}

// th - 0.6, duration - 0.08
void setFreeFallParameters(ADXL345_Address EFF_Address, float threshold, float duration, adxl345_int_t int_no)
{
	u_int8 value = 0;
	I2C_ByteRead(EFF_Address, ADXL345_REG_INT_MAP, &value);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_INT_MAP, value | (int_no << ADXL345_FREE_FALL));
	I2C_ByteRead(EFF_Address, ADXL345_REG_INT_ENABLE, &value);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_INT_ENABLE, value | (1 << ADXL345_FREE_FALL));
	setFreeFallThreshold(EFF_Address, threshold);
	setFreeFallDuration(EFF_Address, duration);
}

// th - 2
void setActivityParameters(ADXL345_Address EFF_Address, float threshold, adxl345_int_t int_no)
{
	u_int8 value = 0;
	I2C_ByteRead(EFF_Address, ADXL345_REG_INT_MAP, &value);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_INT_MAP, value | (int_no << ADXL345_ACTIVITY));
	I2C_ByteRead(EFF_Address, ADXL345_REG_INT_ENABLE, &value);
	I2C_ByteWrite(EFF_Address, ADXL345_REG_INT_ENABLE, value | (1 << ADXL345_ACTIVITY));
	setActivityThreshold(EFF_Address, threshold);
	setYActivity(EFF_Address);
}
