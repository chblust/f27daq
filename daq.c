#include <can.h>
#include "daq.h"
#include "adc.h"

void updateReadings( Sensor* sensors )
{
	for( uint8_t i = 0; i < NUM_SENSORS; ++i )
	{
		if( sensors[i].enabled )
		{
			sensors[i].value = adcRead( sensors[i].channel );
		}
	}
}

void constructCANMessage( CANMessage* message, Sensor* sensors, uint8_t start )
{
	for( uint8_t i = start; i < start + 4 && i < NUM_SENSORS; ++i )
	{
		message->data[i*2] = (sensors[i].value & 0xFF00) >> 8;
		message->data[i*2+1] = (sensors[i].value & 0x00FF);
	}
}

void transmitReadings( Sensor* sensors )
{
	if( sensors[BT_CH].enabled || sensors[SP_CH].enabled || sensors[A1_CH].enabled || sensors[A2_CH].enabled )
	{
		CANMessage message1;
		constructCANMessage( &message1, sensors, 0 );
		sendCAN( &message1 );
	}

	if( sensors[A3_CH].enabled || sensors[A4_CH].enabled || sensors[A5_CH].enabled || sensors[A6_CH].enabled )
	{
		CANMessage message2;
		constructCANMessage( &message2, sensors, 4 );
		sendCAN( &message2 );
	}
}