#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <stdint.h>

#define EN_MAP_ADDR (uint8_t*) 0x10

#define BT_INDEX 0x0
#define SP_INDEX 0x1
#define A1_INDEX 0x2
#define A2_INDEX 0x3
#define A3_INDEX 0x4
#define A4_INDEX 0x5
#define A5_INDEX 0x6
#define A6_INDEX 0x7

#define MESSAGE_INTERVAL_ADDR (uint16_t*) 0x20

uint8_t getBTEnabled();

uint8_t getSPEnabled();

uint8_t getA1Enabled();

uint8_t getA2Enabled();

uint8_t getA3Enabled();

uint8_t getA4Enabled();

uint8_t getA5Enabled();

uint8_t getA6Enabled();

uint16_t getMessageInterval();

void initializeConfiguration();

#endif // CONFIGURATION_H