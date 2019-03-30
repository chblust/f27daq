#include "configuration.h"
#include <avr/eeprom.h>

static uint8_t BTEnabled = 0;

static uint8_t SPEnabled = 0;

static uint8_t A1Enabled = 0;

static uint8_t A2Enabled = 0;

static uint8_t A3Enabled = 0;

static uint8_t A4Enabled = 0;

static uint8_t A5Enabled = 0;

static uint8_t A6Enabled = 0;

static uint16_t messageInterval = 10;

uint8_t getBTEnabled()
{
	return BTEnabled;
}

uint8_t getSPEnabled()
{
	return SPEnabled;
}

uint8_t getA1Enabled()
{
	return A1Enabled;
}

uint8_t getA2Enabled()
{
	return A2Enabled;
}

uint8_t getA3Enabled()
{
	return A3Enabled;
}

uint8_t getA4Enabled()
{
	return A4Enabled;
}

uint8_t getA5Enabled()
{
	return A5Enabled;
}

uint8_t getA6Enabled()
{
	return A6Enabled;
}

uint16_t getMessageInterval()
{
	return messageInterval;
}

void initializeConfiguration()
{
	uint8_t enMap = eeprom_read_byte( EN_MAP_ADDR );

	BTEnabled = (enMap & (1 << BT_INDEX)) != 0;
	SPEnabled = (enMap & (1 << SP_INDEX)) != 0;
	A1Enabled = (enMap & (1 << A1_INDEX)) != 0;
	A2Enabled = (enMap & (1 << A2_INDEX)) != 0;
	A3Enabled = (enMap & (1 << A3_INDEX)) != 0;
	A4Enabled = (enMap & (1 << A4_INDEX)) != 0;
	A5Enabled = (enMap & (1 << A5_INDEX)) != 0;
	A6Enabled = (enMap & (1 << A6_INDEX)) != 0;

	messageInterval = eeprom_read_word( MESSAGE_INTERVAL_ADDR );
}



