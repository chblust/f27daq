#ifndef DAQ_H
#define DAQ_H

#include "sensor.h"
#define NUM_SENSORS 8
#define DAQ_CONFIG_ID 0x0127

// ADC Channel Occupations
#define BT_CH 0
#define SP_CH 1
#define A1_CH 2
#define A2_CH 3
#define A3_CH 4
#define A4_CH 5
#define A5_CH 6
#define A6_CH 7

void updateReadings( Sensor* sensors );

void transmitReadings( Sensor* sensors );

#endif // DAQ_H