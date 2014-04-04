#ifndef _THREADED_UDP_SERVER_H_
#define _THREADED_UDP_SERVER_H_

#include "UDPServer.h"

class UDPServerThread;

/**
 * This class represents a UDP Server which performs its operation in a thread. The thread
 * is an attribute of the class, and it is started only with the start method of this server.
 */
class ThreadedUDPServer : public UDPServer
{
public:

    /**
     * Constructor. The thread object SHOULD NOT be started, this server does it.
     */
    ThreadedUDPServer ( UDPServerThread* thrd ) : UDPServer(), serverThread ( thrd )
    {
    }

    /**
     * Starts the thread of the server
     */
    bool start();

    /**
     * Stops the UDP server
     */
    bool stop();

private:

    // this is the thread of the server
    UDPServerThread* serverThread;
};

#endif

