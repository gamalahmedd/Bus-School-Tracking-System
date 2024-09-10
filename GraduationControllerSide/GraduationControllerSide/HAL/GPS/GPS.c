#include "GPS.h"

void GPS_Init()
{
	GGA_Index = 0;
	memset(GGA_Buffer, 0, Buffer_Size);
	memset(degrees_buffer, 0, degrees_buffer_size);
	
	UART0_Init();
}

void get_gpstime()
{
	GIE_Disable();
	u_int8 time_index = 0;
	
	for (u_int8 index = 0; GGA_Buffer[index] != ','; index++)
	{
		Time_Buffer[time_index] = GGA_Buffer[index];
		time_index++;
	}
	convert_time_to_UTC();
	GIE_Enable();
}

void get_latitude(u_int16 lat_pointer)
{
	GIE_Disable();
	u_int8 lat_index = 0;
	u_int8 index = lat_pointer + 1;
	
	for(; GGA_Buffer[index] != ','; index++)
	{
		Latitude_Buffer[lat_index] = GGA_Buffer[index];
		lat_index++;
	}
	
	Latitude_Buffer[lat_index++] = GGA_Buffer[index++];
	Latitude_Buffer[lat_index] = GGA_Buffer[index];
	convert_to_degrees(Latitude_Buffer);
	GIE_Enable();
}

void get_longitude(u_int16 long_pointer)
{
	GIE_Disable();
	u_int8 long_index = 0;
	u_int8 index = long_pointer + 1;
	
	for(; GGA_Buffer[index] != ','; index++)
	{
		Longitude_Buffer[long_index] = GGA_Buffer[index];
		long_index++;
	}
	
	Longitude_Buffer[long_index++] = GGA_Buffer[index++];
	Longitude_Buffer[long_index] = GGA_Buffer[index];
	convert_to_degrees(Longitude_Buffer);
	GIE_Enable();
}

void get_altitude(u_int16 alt_pointer)
{
	GIE_Disable();
	u_int8 alt_index = 0;
	u_int8 index = alt_pointer + 1;
	
	for(; GGA_Buffer[index] != ','; index++)
	{
		Altitude_Buffer[alt_index] = GGA_Buffer[index];
		alt_index;
	}
	
	Altitude_Buffer[alt_index] = GGA_Buffer[index + 1];
	GIE_Enable();
}

void convert_time_to_UTC()
{
	unsigned int hour, min, sec;
	uint32_t Time_value;
	
	Time_value = atol(Time_Buffer);       /* convert string to integer */
	hour = (Time_value / 10000);          /* extract hour from integer */
	min  = (Time_value % 10000) / 100;    /* extract minute from integer */
	sec  = (Time_value % 10000) % 100;    /* extract second from integer*/

	sprintf(Time_Buffer, "%d:%d:%d", hour,min,sec);
	
}

void convert_to_degrees(char *raw){
	
	double value;
	float decimal_value,temp;
	
	int32_t degrees;
	
	float position;
	value = atof(raw);    /* convert string into float for conversion */
	
	/* convert raw latitude/longitude into degree format */
	decimal_value = (value/100);
	degrees       = (int)(decimal_value);
	temp          = (decimal_value - (int)decimal_value)/0.6;
	position      = (float)degrees + temp;
	
	dtostrf(position, 6, 4, degrees_buffer);  /* convert float value into string */
}