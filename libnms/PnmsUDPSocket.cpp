#include "PnmsUDPSocket.h"

/**
 * Sends the given message through the wire
 */
bool PnmsUDPSocket::send ( CommandInterface* message )
{
    return UDPSocket::send ( message->asString() );
}

