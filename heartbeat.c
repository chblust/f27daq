#include "heartbeat.h"
#include <port.h>

/*
 * Turn the heartbeat LED of the daq on or off.
 * @param[in] d - 0 for off, 1 for on
 *
 */
void setHeartBeat( uint8_t d )
{
	writePortC( HEARTBEAT_INDEX, d );
}