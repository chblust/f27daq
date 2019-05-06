#include <can.h>
#include "daq.h"
#include "adc.h"
#include <util/delay.h>

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
	for( uint8_t i = start; (i < start + 4) && (i < NUM_SENSORS); ++i )
	{
		message->data[(i-start)*2] = (uint8_t)((((uint16_t)sensors[i].value) & 0xFF00) >> 8);
		message->data[(i-start)*2+1] = (uint8_t)(((uint16_t)sensors[i].value) & 0x00FF);
	}
}

void transmitReadings( Sensor* sensors )
{
	if( sensors[BT_CH].enabled || sensors[SP_CH].enabled || sensors[A1_CH].enabled || sensors[A2_CH].enabled )
	{
		CANMessage message1;
		message1.id = 0x10;
		message1.length = 8;
		//constructCANMessage( &message1, sensors, 0 );
		message1.data[0] = (sensors[0].value & 0xFF00) >> 8;
		message1.data[1] = (sensors[0].value & 0xFF);
		sendCAN( &message1 );
	}
	_delay_ms(5);
	if( sensors[A3_CH].enabled || sensors[A4_CH].enabled || sensors[A5_CH].enabled || sensors[A6_CH].enabled )
	{
		CANMessage message2;
		message2.id = 0x20;
		message2.length = 8;
		constructCANMessage( &message2, sensors, 4 );
		sendCAN( &message2 );
	}
}