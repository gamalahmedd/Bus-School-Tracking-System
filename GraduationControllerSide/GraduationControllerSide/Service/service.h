#ifndef SERVICE_H_
#define SERVICE_H_
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "../../HAL/ADXL345/ADXL345.h"
#include "../../HAL/LCD/LCD.h"
#include "../../HAL/ESP01/ESP01.h"
#include "../../HAL/MFRC/mfrc522.h"
#include "../../HAL/GPS/GPS.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/GIE/GIE.h"
#include <avr/interrupt.h>
#define ESP_PRIORITY 9
#define GPS_PRIORITY 8
#define RFID_PRIORITY 7

/*------------------------------------------Function Definition---------------------------------------*/

void System_Init(void);
void ESP01_CheckConnectionTask(void *pvParam);
void GPS_GetLocationTask(void *pvParam);
void RFID_TakeAttendance(void *pvParam);
portSHORT startScheduler();

/*------------------------------------------RTOS Variables----------------------------------------*/
SemaphoreHandle_t ESP_SEM;
QueueHandle_t CHECK_CONNECTION;




#endif /* SERVICE_H_ */