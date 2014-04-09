#include "ThreadedTCPServer.h"
#include "TCPServerThread.h"

/**
 * Starts the server
 */
bool ThreadedTCPServer::start()
{
    serverThread->setServer ( this );
    if ( serverThread->isStarted() )
    {
        return false;
    }
    bool succ = serverThread->start();
    if ( succ )
    {
        return true;
    }
    return false;
}

/**
 * Stops the server
 */
bool ThreadedTCPServer::stop()
{
    serverThread->stop();
    serverThread->waitToFinish();

    return true;
}
