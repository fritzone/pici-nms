#include "DaemonMessageHandlerThread.h"
#include "DaemonMessageHandler.h"
#include "DaemonMutex.h"

#include "Logger.h"

#include <sstream>

using namespace std;

DaemonMutex DaemonMessageHandlerThread::messageMutex;

/**
 * Constructor
 */
DaemonMessageHandlerThread::DaemonMessageHandlerThread ( Daemon* dmn ) : Thread(), daemon ( dmn )
{

}


/**
 * The thread's function
 */
void* DaemonMessageHandlerThread::process()
{
    messageMutex.lock();
    if ( !DaemonMessageHandler::handleMessage ( msg, &addrs, daemon, NULL ) )
    {
        LOG ( "Message was not handled" );
    }
    messageMutex.unlock();
    return NULL;
}

/**
 * Starts the actual thread that will handle the message
 */
bool DaemonMessageHandlerThread::handleMessage ( std::string message, NetworkAddress fromAddr )
{
    LOG ( message );
    msg = message;
    addrs = fromAddr;
    return start();
}
