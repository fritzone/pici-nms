#ifndef _CONNECTION_THREAD_H_
#define _CONNECTION_THREAD_H_

#include "Thread.h"

class Connection;
class AbstractSocket;
class TransporterImpl;
class Mutex;

/**
 * Class responsible for one connection's thread.
 */
class ConnectionThread: public Thread
{
public:

    /**
     * Constructor.
     */
    ConnectionThread ( Connection* );

    /**
     * Does the threads work
     */
    virtual void* process();

private:

    // mutex for the connection thread
    static Mutex connectionThreadMutex;

private:

    // the connection object of the class
    Connection* connection;


};

#endif
