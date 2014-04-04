#include "Logger.h"
#include "LocalTCPClient.h"
#include "Connection.h"
#include "ConnectionThread.h"
#include "NetworkAddress.h"

LocalTCPClient::LocalTCPClient ( TransporterImpl* tr ) : AbstractServerClient(), transp ( tr )
{
}

bool LocalTCPClient::onConnect ( AbstractSocket* sock, NetworkAddress* addr )
{
    //printf("New connection being created");
    Connection* conn = new ( std::nothrow ) Connection ( sock, transp );        // will be deleted when the thread finishes
    if ( NULL == conn )
    {
        LOG_ERR ( "Not enough memory to create a new Connection object" );
        delete addr;
        return false;
    }
    ConnectionThread* connThread = new ( std::nothrow ) ConnectionThread ( conn );
    if ( NULL == connThread )
    {
        LOG_ERR ( "Not enough memory to create a new Connection thread" );
        delete conn;
        delete addr;
        return false;
    }
    bool started = connThread->start();
    if ( !started )
    {
        LOG ( "Cannot start the connection thread" );
        delete conn;
        delete connThread;
        delete addr;
        return false;
    }
    delete addr;
    return true;
}
