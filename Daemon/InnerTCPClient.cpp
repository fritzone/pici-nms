#include "InnerTCPClient.h"
#include "DaemonMessageHandler.h"

#include "Logger.h"

#include <sstream>

using namespace std;

/**
 * Constructor, creates a new Inner TCP client object
 */
InnerTCPClient::InnerTCPClient ( Daemon* dmn ) : AbstractServerClient(), daemon ( dmn )
{
}

/**
 * Called when a new client has connected to the daemon
 */
bool InnerTCPClient::onConnect ( AbstractSocket* sock, NetworkAddress* addr )
{
    LOG ( "New TCP client connected" );

    string msg = sock->receive();       // receive the message itself
    stringstream ss;
    ss << msg.length();
    LOG ( msg );
    // and handle it
    if ( !DaemonMessageHandler::handleMessage ( msg, addr, daemon, sock ) )
    {
        LOG ( "Could not handle the message" );
        return false;
    }
    return true;
}
