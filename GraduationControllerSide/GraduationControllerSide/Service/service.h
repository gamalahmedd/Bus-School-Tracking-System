#ifndef SERVICE_H_
#define SERVICE_H_
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "../../HAL/ADXL345/ADXL345.h"
#include "../../HAL/LCD/LCD.h"
#include "../../HAL/ESP01/ESP01.h"
#include "../../HAL/MFRC/mfrc522.h"
#include "../../HAL/GPS/GPS.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/GIE/GIE.h"
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#define ESP_PRIORITY 9
#define ADXL_PRIORITY 8
#define GPS_PRIORITY 7
#define RFID_PRIORITY 7
#define GPS_BIT (1 << 0)
#define RFID_BIT (1 << 1)
#define ADXL_BIT (1 << 2)

/*------------------------------------------Function Definition---------------------------------------*/

void System_Init(void);
void ESP01_CheckConnectionTask(void *pvParam);
void GPS_GetLocationTask(void *pvParam);
void RFID_TakeAttendance(void *pvParam);
void ADXL_SendAccidentAlertTask(void *pvParam);
void ADXL_SendAccelerationAlertTask(void *pvParam);
void startScheduler();

/*------------------------------------------RTOS Variables----------------------------------------*/
SemaphoreHandle_t ESP_SEM;
SemaphoreHandle_t ACCIDENT_SEM;
SemaphoreHandle_t GPS_SEM;
SemaphoreHandle_t ACCELERATION_SEM;
EventGroupHandle_t CHECK_CONNECTION;
SemaphoreHandle_t UART1_SEND;
u_int8 Reg;


#endif /* SERVICE_H_ */