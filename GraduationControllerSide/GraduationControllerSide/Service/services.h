
#ifndef SERVICES_H_
#define SERVICES_H_

#include "FreeRTOS.h"
#include "task.h"


#include "../MCAL/DIO/DIO.h"
#include "../LIB/STD_TYPES.h"
#include "../HAL/MFRC/mfrc522.h"
#include "../MCAL/UART/UART.h"




#define RFID_PRIORITY   1	

#define GPS_PRIORITY    2

#define ADXL_PRIORITY   3



/*-------------------------------RFID VARIBELS---------------------------------*/
uint8_t byte;
uint8_t str[MAX_LEN];
uint8_t person_recognised = 0;

uint8_t data_recieved = 0;
/*----------------------------------------------------------------------------*/

/*-------------------------------GPS VARIBELS---------------------------------*/

/*----------------------------------------------------------------------------*/


/*-------------------------------ADXL VARIBELS---------------------------------*/

/*----------------------------------------------------------------------------*/

#endif /* SERVICES_H_ */