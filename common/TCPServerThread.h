#ifndef _TCPSERVER_THREAD_H_
#define _TCPSERVER_THREAD_H_

#include "Thread.h"

class ThreadedTCPServer;

/**
 * This class represents a thread can be the "running" part of a ThreadedTCPServer
 */
class TCPServerThread : public Thread
{
public:

    /**
     * Constructor
     */
    TCPServerThread() : Thread(), server ( NULL )
    {
    }

    /**
     * Sets the server object of this class
     */
    void setServer ( ThreadedTCPServer* srv );

protected:

    /**
     * This method must be overridden by thread classes
     */
    virtual void* process();

private:

    // the server object
    ThreadedTCPServer* server;

};

#endif
