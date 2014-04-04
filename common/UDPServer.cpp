#include "UDPServer.h"
#include "UDPSocket.h"
#include "Logger.h"

/**
 * Constructor
 */
UDPServer::UDPServer() : BasicServerImpl()
{
    sock = new ( std::nothrow ) UDPSocket();
    if ( NULL == sock )
    {
        LOG_ERR ( "Not enough memory to create a new UDPSocket" );
    }
}

UDPServer::UDPServer ( ClientAcceptor* acc ) : BasicServerImpl ( acc )
{
    sock = new ( std::nothrow ) UDPSocket();
    if ( NULL == sock )
    {
        LOG_ERR ( "Not enough memory to create a new UDPSocket" );
    }
}

/**
 * Returns the socket object of the server
 * @return the socket
 */
UDPSocket* UDPServer::getSocket() const
{
    return dynamic_cast<UDPSocket*> ( sock );
}
