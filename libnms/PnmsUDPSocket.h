#ifndef _PNMSUDPSOCKET_H_
#define _PNMSUDPSOCKET_H_

#include "UDPSocket.h"
#include "CommandInterface.h"

/**
 * UDP Socket used in the PICI-NMS framework to send/receive messages through the UDP interface.
 */
class PnmsUDPSocket : public UDPSocket
{
public:

	/**
	 * Constructor, creates a PICI-NMS UDP socket
	 */
	PnmsUDPSocket() : UDPSocket()
	{
	}

	/**
	 * Sends a message to the Network Address connected to this socket
	 * @param message - the message that is sent through the wire to the other components
	 */
	bool send(CommandInterface* message);

};

#endif

