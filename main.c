#include <stdint.h>
#include <can.h>
#include <avr/eeprom.h>
#include <timer.h>
#include <util/delay.h>
#include "configuration.h"
#include "adc.h"
#include "heartbeat.h"
#include "daq.h"

/**
 * Write data to an eeprom address, all specified by the given CAN message.
 * @param[in] message - the CAN message
 *
 */
void handleConfigurationMessage( CANMessage* message )
{
	// Extract the address and the length from the message
	uint8_t* address = (uint8_t*) ((message->data[0] << 8) | message->data[1]);
	uint8_t length = message->data[2];

	// Write the data to either a word or a byte in eeprom
	if( length == 1 )
	{
		uint8_t toWrite = message->data[3];
		eeprom_write_byte( address, toWrite );
	}
	else
	{
		uint16_t toWrite = (message->data[3] << 8) | message->data[4];
		eeprom_write_word( (uint16_t*)address, toWrite );
	}

	// Read the updated values from eeprom
	initializeConfiguration();
}

int main()
{
	// Turn off the heartbeat LED
	setHeartBeat(0);
	initializeConfiguration();

	initCAN();
	listenForMessage( DAQ_CONFIG_ID, 8 );

	initADC(0x06);
	

	initTimer();
	// Currently defaulting to 10ms intervals
	setTimer( 10 );//getMessageInterval() );

	Sensor sensors[NUM_SENSORS];
	for( uint8_t i = 0; i < NUM_SENSORS; ++i )
	{
		defaultSensor( &sensors[i] );
	}

	sensors[BT_CH].channel = BT_CH;
	sensors[SP_CH].channel = SP_CH;
	sensors[A1_CH].channel = A1_CH;
	sensors[A2_CH].channel = A2_CH;
	sensors[A3_CH].channel = A3_CH;
	sensors[A4_CH].channel = A4_CH;
	sensors[A5_CH].channel = A5_CH;
	sensors[A6_CH].channel = A6_CH;

	uint8_t heartBeat = 0;

	while( 1 )
	{
		CANMessage received;

		// Handle configuration messages if they arrive
		if( getMessage( &received ) )
		{
			handleConfigurationMessage( &received );
		}
		
		// Update readings every loop
		updateReadings( sensors );

		// If the timer has expired, send the CAN message(s)
		// with the ADC readings
		if( getTimeElapsed() )
		{
			heartBeat ^= 1;
			setHeartBeat( heartBeat );
			transmitReadings( sensors );
		}
	}	
}





