#include "ThreadedUDPServer.h"
#include "UDPServerThread.h"
#include "Logger.h"
#include "UDPSocket.h"

/**
 * Starts the server
 */
bool ThreadedUDPServer::start()
{
    serverThread->setServer ( this );
    LOG ( "Starting UDP server" );
    if ( serverThread->isStarted() )
    {
        LOG_ERR("Server thread is already started");
        return false;
    }
    bool succ = serverThread->start();
    if ( succ )
    {
        LOG("Started succesfully");
        return true;
    }
    LOG_ERR ( "Could not start the UDP Server's thread" );
    return false;
}

/**
 * Stops the UDP Server
 */
bool ThreadedUDPServer::stop()
{
    serverThread->stop();
    this->getSocket()->close();
    serverThread->waitToFinish();
    return true;
}
