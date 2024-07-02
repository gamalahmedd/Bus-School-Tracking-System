#ifndef ADXL345_H_
#define ADXL345_H_

#include "../../LIB/Clock.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BITMATH.h"
#include "../../MCAL/TWI/TWI.h"
#include "ADXL345_Types.h"
#include "ADXL345_reg.h"
#include "ADXL345_Config.h"

void Accelerometor_init();

void Accelerometor_ReadAxis(volatile ADXL345_Data *Data_ptr);

void setActivityParameters();
void setFreeFallParameters();

float constrain(float amt, float low, float high);

void setRange(adxl345_range_t range);
void setDataRate(adxl345_dataRate_t dataRate);

void clearSettings();

#endif
