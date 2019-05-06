#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

typedef struct 
{
	uint16_t value;
	uint16_t channel: 3;
	uint16_t enabled : 1;
} Sensor;

void defaultSensor( Sensor* sensor );

#endif // SENSOR_H