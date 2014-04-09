#ifndef _THREADED_TCP_SERVER_H_
#define _THREADED_TCP_SERVER_H_

#include "TCPServer.h"

class TCPServerThread;

/**
 * This class represents a TCP Server which performs its operation in a thread. The thread
 * is an attribute of the class, and it is started only with the start method of this server.
 */
class ThreadedTCPServer : public TCPServer
{
public:

    /**
     * Constructor. The thread object SHOULD NOT be started, this server does it.
     */
    ThreadedTCPServer ( TCPServerThread* thrd ) : TCPServer(), serverThread ( thrd )
    {
    }

    /**
     * Starts the thread of the server
     */
    bool start();

    /**
     * Stops the server
     */
    bool stop();

    TCPServerThread* thread()
    {
        return serverThread;
    }

private:

    // this is the thread of the server
    TCPServerThread* serverThread;
};

#endif

