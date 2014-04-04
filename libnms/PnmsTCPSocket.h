#ifndef _PNMS_TCPSOCKET_H_
#define _PNMS_TCPSOCKET_H_

#include "TcpSocket.h"
#include "CommandInterface.h"

class PnmsTCPSocket : public TCPSocket
{
public:
    PnmsTCPSocket() : TCPSocket()
    {
    }

    PnmsTCPSocket ( const NetworkAddress* whereTo ) : TCPSocket()
    {
        TCPSocket::connectTo ( whereTo );
    }

    /**
     * Sends the given command to the dispatcher using the simples form of synchronization,
     * the classical send size, receive ack, send message, receive ack method implemented
     * currently in the dispatcher.
     * @param cmd - the command to send
     */
    string send ( CommandInterface* cmd, bool needsAck = true );

    /**
     * Sends the given command through the socket, and waits for timeout milliseconds for a reply before
     * returning
     */
    string send ( CommandInterface* cmd, int timeout );
};

#endif
