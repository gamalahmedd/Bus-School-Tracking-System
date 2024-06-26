/*
 * ADXL345_Config.h
 *
 * Created: 26/06/2024 01:53:08 ص
 *  Author: hanaa
 */ 


#ifndef ADXL345_CONFIG_H_
#define ADXL345_CONFIG_H_
 
#define Slave_Address            ADXL345_ALTERNATIVE_ADDRESS       //SDO --> GND
#define Mode                     ADXL345_MessureMode
#define Range                    ADXL345_RANGE_2G                //full resolution , +/-2g
#define BW_RATE                  ADXL345_DATARATE_100HZ                // 100 Hz data rate
#define ACT_Threshold_Val        2
#define ACT_INTERRupt_NO         ADXL345_INT2
#define ACT_AXIS                 0x20                // Y-Axis
#define FF_Threshold_Val         1
#define FF_INTERRupt_NO          ADXL345_INT1
#define FF_Duration              0.08




#endif /* ADXL345_CONFIG_H_ */