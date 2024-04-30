#include "FreeRTOS.h"
#include "task.h"
#include "LCD.h"

#define  TASK1_PRIORITY (8)
#define  TASK2_PRIORITY (3)

void task1_code(void*pvParamter);
void task2_code(void*pvParamter);

portSHORT main(void)
{
	LCD_Init();
	
	//Create Tasks
	xTaskCreate(task1_code, "Task1", configMINIMAL_STACK_SIZE, NULL, TASK1_PRIORITY, NULL);
	xTaskCreate(task2_code, "Task2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, NULL);
	
	vTaskStartScheduler();
    while (1) 
    {
    }
}

void task1_code(void *pvParamter)
{
	while(1)
	{
		LCD_ClearScreen();
		LCD_SendString("I'm Task 1", 1, 1);
		_delay_ms(1000);
	}
}

void task2_code(void*pvParamter)
{
	while(1)
	{
		LCD_ClearScreen();
		LCD_SendString("I'm Task 2", 1, 1);
		vTaskDelay(2000);
	}
}