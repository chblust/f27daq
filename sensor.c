#include "sensor.h"

void defaultSensor( Sensor* sensor )
{
	sensor->enabled = 0;
	sensor->value = 0;
	sensor->channel = 0;
}