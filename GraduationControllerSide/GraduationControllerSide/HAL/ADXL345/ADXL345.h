/*
 * ADXL345.h
 *
 *  Created on: 1/2/2024
 *  Author: Hanaa
 */

#ifndef ADXL345_H_
#define ADXL345_H_

// edit these includes
#include "../../LIB/Clock.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BITMATH.h"
#include "../../MCAL/TWI/TWI.h"

#include "ADXL345_Types.h"
#include "ADXL345_reg.h"

void Accelerometor_init(ADX345_PowerModes Mode, ADXL345_Address EFF_Address);

void Accelerometor_ReadAxis(ADXL345_Address EFF_Address, volatile ADXL345_Data *Data_ptr);

void setActivityParameters(ADXL345_Address EFF_Address, float threshold, adxl345_int_t int_no);
void setFreeFallParameters(ADXL345_Address EFF_Address, float threshold, float duration, adxl345_int_t int_no);
void setYActivity(ADXL345_Address EFF_Address);
void setActivityThreshold(ADXL345_Address EFF_Address, float threshold);

void setFreeFallDuration(ADXL345_Address EFF_Address, float duration);
void setFreeFallThreshold(ADXL345_Address EFF_Address, float threshold);
float constrain(float amt, float low, float high);

void setRange(ADXL345_Address EFF_Address, adxl345_range_t range);
void setDataRate(ADXL345_Address EFF_Address, adxl345_dataRate_t dataRate);
void clearSettings(ADXL345_Address EFF_Address);

#endif
