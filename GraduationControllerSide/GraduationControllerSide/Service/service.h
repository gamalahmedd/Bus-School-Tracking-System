#ifndef SERVICE_H_
#define SERVICE_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"
#include "semphr.h"
#include "../../HAL/ADXL345/ADXL345.h"
#include "../../HAL/LCD/LCD.h"
#include "../../HAL/ESP01/ESP01.h"
#include "../../HAL/MFRC/mfrc522.h"
#include <avr/interrupt.h>

void System_Init(void);
void ESP01_CheckConnectionTask(void *pvParam);
portSHORT startScheduler();

#endif /* SERVICE_H_ */