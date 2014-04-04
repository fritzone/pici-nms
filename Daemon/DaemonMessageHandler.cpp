#include "DaemonMessageHandler.h"
#include "Daemon.h"
#include "DispatcherRequest.h"
#include "RegisteredDispatcher.h"

#include "CommandUtils.h"
#include "Logger.h"
#include "NetworkAddress.h"
#include "UDPSocket.h"
#include "Host.h"
#include "MessageDigest.h"

#include <sstream>
#include <string.h>

using namespace std;

/**
 * Handles the NMS_INIT message
 */
bool DaemonMessageHandler::handleInitMessage ( const std::string& s, NetworkAddress* fromAddr, Daemon* daemon, AbstractSocket* respSock )
{
    LOG ( "Got a message" );
    LOG ( s );
    DispatcherRequest dispatcherRequest ( s );
    if ( dispatcherRequest.isValid() )
    {
        // here we have to check if on the requested port there is a dispatcher
        bool found = false;
        RegisteredDispatcher* regd = NULL;
        for ( unsigned int i = 0; i < daemon->getDispatchers().size (); i++ )
        {
            if ( daemon->getDispatchers() [i]->getPort () == dispatcherRequest.getPort () )
            {
                found = true;
                regd = daemon->getDispatchers() [i];
            }
        }
        stringstream ss;

        if ( found && regd != NULL )
        {
            ss << "NMS_OK#" << Daemon::getNextDynamicHost() << "@" << dispatcherRequest.getProtocol() << ":"
               << regd->getIp() << ":" << dispatcherRequest.getPort();
        }
        else
        {
            ss << "NMS_ERR:NO_DISPATCHER:" << dispatcherRequest.getPort();
        }

        // and create a response socket
        if ( respSock == NULL )
        {
            UDPSocket responseSock;
            responseSock.connectTo ( fromAddr );
            if ( !responseSock.send ( ss.str() ) )
            {
                LOG_ERR ( "Cannot send a response to a dynamic client" );
                responseSock.close();
                return false;
            }
            responseSock.close();
        }
        else
        {
            if ( !respSock->send ( ss.str() ) )
            {
                LOG_ERR ( "Cannot send a response back to the initiaing client" );
                return false;
            }
        }

        LOG ( ss.str() );
        return true;
    }
    else
    {
        LOG_ERR ( "Dispatcher request is invalid" );
        return false;
    }
}

/**
 * Generates a new sitekey from the old one. The procedure is very simple, the
 * return value is the SHA key of the old site ID. Just as a remembrance, the
 * very first sitekey is generated on the install of the dispatcher. From this
 * point on, all the sitekeys are just SHA values ofthe old sitekey. This way
 * the dispatcher knows that the daemon is a real deamon, and the daemon knows
 * that the dispatcher is the one that has got the previous sitekey.
 */
string DaemonMessageHandler::generateNewSitekey ( const std::string& oldSitekey )
{
    return MessageDigest::getHashCode ( oldSitekey );
}

/**
 * Handles the DSP_INIT message, returns DSP_OK#id:sitekey
 */
bool DaemonMessageHandler::handleDispInitMessage ( const std::string& s, NetworkAddress* fromAddr, Daemon* daemon, AbstractSocket* respSock )
{
    if ( NULL == respSock )
    {
        LOG_ERR ( "Invalid dispatcher init request" );
        return false;
    }
    string ls = s;  // will contain a local copy of the s
    string cmd = CommandUtils::consume ( ls, '(' );
    string prot = CommandUtils::consume ( ls, ':' );
    if ( prot.length() != 3 )
    {
        LOG_ERR ( "Invalid Disp Ini message" );
        return false;
    }
    string ip = CommandUtils::consume ( ls, ':' );

    if ( !NetworkAddress::validIp ( ip ) )
    {
        LOG_ERR ( "Invalid IP Address supplied by the Dispatcher in the DSP_INIT" );
        return false;
    }
    // here check whether the IP and the fromAddr are the same or not ...
    // and also check whether the IP is in the list of acknowledged dispatcher IPs

    string port = CommandUtils::consume ( ls, ':' );
    if ( port.length() < 3 )
    {
        LOG_ERR ( "Invalid port in the DSP_INIT message" );
        return false;
    }

    stringstream ss;
    string sitekey = CommandUtils::consume ( ls, ')' );
    if ( !daemon->isValidSitekey ( sitekey, fromAddr ) )
    {
        LOG_ERR ( "Sitekey validation failed" );
        ss << "DSP_ERROR:SITEKEY_INVALID";
    }
    else
    {
        string newSiteKey = generateNewSitekey ( sitekey );
        ss << "DSP_OK#" << Daemon::getNextDispatcherId() << ":" << newSiteKey ;
    }

    // add the dispatcher to the daemon internals
    daemon->addDispatcher ( ip, port, sitekey );

    LOG ( "Sending" );
    LOG ( ss.str() );
    if ( !respSock->send ( ss.str() ) )
    {
        LOG_ERR ( "Cannot send reply to the dispatcher" );
        return false;
    }

    return true;
}



/**
 * Returns true if the string is a serialized init message
 */
bool DaemonMessageHandler::isInitMessage ( const string& s )
{
    return strncmp ( s.c_str(), "NMS_INIT", 8 ) == 0;
}

/**
 * Returns true if the string is a serialized init message
 */
bool DaemonMessageHandler::isDispInitMessage ( const string& s )
{
    return strncmp ( s.c_str(), "DSP_INIT", 8 ) == 0;
}


/**
 * Handles the message that was received by the daemon.
 */
bool DaemonMessageHandler::handleMessage ( const std::string& s, NetworkAddress* fromAddr, Daemon* daemon, AbstractSocket* respSock )
{
    if ( s.length() < 8 ) // this is here to avoid the case when someone wants to send lots of short message to "break" the daemon
    {
        return false;
    }

    if ( isInitMessage ( s ) )
    {
        return handleInitMessage ( s, fromAddr, daemon, respSock );
    }

    if ( isDispInitMessage ( s ) )
    {
        return handleDispInitMessage ( s, fromAddr, daemon, respSock );
    }

    return false;
}
