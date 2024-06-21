#include "service.h"


portSHORT startScheduler()
{
	System_Init();
	
	
}

void System_Init()
{
	ESP01_Init();
	Accelerometor_init();
	LCD_Init();
	mfrc522_init();
}

void ESP01_CheckConnectionTask(void *pvParam)
{
	while(1)
	{
		
	}
}