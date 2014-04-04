#ifndef _UDPSERVER_THREAD_H_
#define _UDPSERVER_THREAD_H_

#include "Thread.h"

class ThreadedUDPServer;

/**
 * This class represents a thread can be the "running" part of a ThreadedUDPServer
 */
class UDPServerThread : public Thread
{
public:

    /**
     * Constructor
     */
    UDPServerThread() : Thread(), server ( NULL )
    {
    }

    /**
     * Sets the server object of this class
     */
    void setServer ( ThreadedUDPServer* srv );

protected:

    /**
     * This method must be overridden by thread classes
     */
    virtual void* process() = 0;

protected:

    // the server object
    ThreadedUDPServer* server;
};

#endif
