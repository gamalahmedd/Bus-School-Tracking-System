#ifndef GPS_H_
#define GPS_H_
#include "GPS_Types.h"

void GPS_Init();
void convert_time_to_UTC();
void convert_to_degrees(char *);
void get_gpstime();
void get_latitude(u_int16 lat_pointer);
void get_longitude(u_int16 long_pointer);
void get_altitude(u_int16 alt_pointer);

#endif