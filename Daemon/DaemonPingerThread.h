#ifndef _DAEMON_PINGER_THREAD_H_
#define _DAEMON_PINGER_THREAD_H_

#include "Thread.h"

class Daemon;

/**
 * Class responsible fro pinging the dispatchers
 */
class DaemonPingerThread : public Thread
{
public:

    /**
     * Constructor
     */
    DaemonPingerThread ( Daemon* _dmn );

    ~DaemonPingerThread();

protected:

    /**
     * Processes pings all the daemons at some interval
     */
    virtual void* process();

private:

    // the daemon associated with this thread
    Daemon* dmn;

};

#endif
