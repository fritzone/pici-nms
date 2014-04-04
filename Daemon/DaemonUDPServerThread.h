#ifndef _DAEMON_UDP_SERVER_THREAD_H_
#define _DAEMON_UDP_SERVER_THREAD_H_

#include <UDPServerThread.h>

#include <vector>
#include <string>

using namespace std;

class TransporterInfo;
class Daemon;
class DaemonMutex;

/**
 * This class represents the Daemon's UDP server's thread. Its main scope is to
 * receive connection enquiries from not securized clients.
 */
class DaemonUDPServerThread : public UDPServerThread
{
public:

    /**
     * Constructor
     */
    DaemonUDPServerThread ( Daemon* );

    /**
     * Processes the threads
     */
    virtual void* process();

private:

    // mutex for the UDP thread
    static DaemonMutex udpMutex;

private:

    // the daemon running this thread
    Daemon* daemon;
};

#endif
