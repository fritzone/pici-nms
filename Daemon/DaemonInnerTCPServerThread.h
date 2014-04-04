#ifndef _DAEMON_INNER_TCP_SERVER_THREAD_H_
#define _DAEMON_INNER_TCP_SERVER_THREAD_H_

#include "TCPServerThread.h"

class Daemon;

/**
 * Thread of the TCP Server for the inner network
 */
class DaemonInnerTCPServerThread : public TCPServerThread
{
public:

    /**
     * Constructor
     */
    DaemonInnerTCPServerThread ( Daemon* );

private:

    // the daemon which holds this thread
    Daemon* daemon;
};

#endif
