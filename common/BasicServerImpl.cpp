#include "Logger.h"
#include "BasicServerImpl.h"
#include "NetworkAddress.h"
#include "AbstractSocket.h"
#include "SocketErrorCodes.h"

/**
 * Constructor
 */
BasicServerImpl::BasicServerImpl() : AbstractServer ( NULL ),  sock ( NULL ), address ( NULL )
{
}

/**
 * Constructor
 */
BasicServerImpl::BasicServerImpl ( ClientAcceptor* acc ) : AbstractServer ( acc ),  sock ( NULL ), address ( NULL )
{
}

/**
* Binds the server to the given address
*/
bool BasicServerImpl::bind ( NetworkAddress* addr )
{
#ifdef _WIN32
    BOOL excad = TRUE;
    if ( ::setsockopt ( this->sock->theSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, ( const char* ) &excad, sizeof ( excad ) ) == SOCKET_ERROR )
    {
        populateErrorCode();
        LOG ( getError() );
        clearError();
    }
#endif

    int errCode = ::bind ( this->sock->theSocket, ( SOCKADDR* ) & ( addr->address ), sizeof ( addr->address ) );
    if ( SOCKET_ERROR == errCode )
    {
        populateErrorCode (
#ifndef _WIN32
            SocketErrorCodes::OPERATION_BIND
#endif
        );
        LOG ( "Bind error" );
        LOG ( addr->getIp() );
        return false;
    }
    return true;
}
