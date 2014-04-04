#include "SecureClientInitializer.h"
#include "PnmsTCPSocket.h"
#include "CommandNMS_INIT.h"
#include "ClientConfiguration.h"

#include "NetworkAddress.h"
#include "Logger.h"

#include <string>

using namespace std;

/**
 * Constructor
 */
SecureClientInitializer::SecureClientInitializer()
{
    cfg = new ( std::nothrow ) ClientConfiguration();
    if ( NULL == cfg )
    {
        LOG_ERR ( "Not enough memory to create a ClientConfiguration" );
        forceFail();
        return;
    }

    if ( cfg->initialized() )
    {
        forceSuccess();
    }
    else
    {
        LOG_ERR ( "Client was not initialized succesfully" );
        forceFail();
    }
}

/**
 * Constructor
 */
SecureClientInitializer::SecureClientInitializer ( const std::string& configFile )
{
    cfg = new ( std::nothrow ) ClientConfiguration ( configFile );
    if ( NULL == cfg )
    {
        LOG_ERR ( "Not enough memory to create a new Clientconfiguration" );
        forceFail();
        return;
    }
    if ( cfg->initialized() )
    {
        forceSuccess();
    }
    else
    {
        LOG_ERR ( "Client was not initialized succesfully" );
        forceFail();
    }
}

SecureClientInitializer::~SecureClientInitializer()
{
    delete cfg;
}

/**
 * Initializes a secure client
 */
bool SecureClientInitializer::initializeClient()
{
    if ( !basicInit() )
    {
        LOG ( "Basic initialization failed" );
        return false;
    }

    PnmsTCPSocket tcpToDaemon;
    if ( !tcpToDaemon.isInitialized() )
    {
        LOG ( "Cannot create TCP socket to daemon" );
        return false;
    }
    NetworkAddress dispAddr ( cfg->getDaemonIP(), cfg->getDaemonTCPPort() );
    if ( !tcpToDaemon.connectTo ( &dispAddr ) )
    {
        LOG ( "Cannot connect to Daemon using TCP" );
        tcpToDaemon.close();
        return false;
    }
    CommandNMS_INIT initm ( CONFIG_DISPATCHER_PROTOCOL, cfg->preferredDispatcherPort() );
    string ack = tcpToDaemon.send ( &initm );;
    if ( ack.length() == 0 )
    {
        LOG ( "Cannot send NMSINIT to daemon" );
        tcpToDaemon.close();
        return false;
    }

    if ( !analyzeResponse ( ack.c_str() ) )
    {
        LOG ( "Invalid response from the daemon" );
        tcpToDaemon.close();
        return false;
    }

    tcpToDaemon.close();
    return true;
}

bool SecureClientInitializer::initialized() const
{
    return cfg->initialized();
}