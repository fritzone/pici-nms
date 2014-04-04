#include "ClientConfiguration.h"
#include "ConfigReader.h"

/**
 * Search for the config file
 */
ClientConfiguration::ClientConfiguration() : initSuccess ( true )
{
    cfg = new ( std::nothrow ) ConfigReader ( "client.xml" );
    if ( !cfg->configLoaded() )
    {
        initSuccess = false;
    }
}

ClientConfiguration::ClientConfiguration ( const std::string& directory ) : initSuccess ( true )
{
    cfg = new ( std::nothrow ) ConfigReader ( "client.xml", directory );
    if ( !cfg->configLoaded() )
    {
        initSuccess = false;
    }
}

ClientConfiguration::~ClientConfiguration()
{
    delete cfg;
}

string ClientConfiguration::getDaemonIP()
{
    if ( cfg )
    {
        return cfg->getValue ( "daemon", "network", "IP" );
    }
    return "";
}

int ClientConfiguration::getDaemonTCPPort()
{
    if ( cfg )
    {
        string s = cfg->getValue ( "daemon", "socketinfo", "tcpport" );
        return atoi ( s.c_str() );
    }
    return 0;
}

int ClientConfiguration::preferredDispatcherPort()
{
    if ( cfg )
    {
        string s = cfg->getValue ( "dispatcher", "port", "value" );
        return atoi ( s.c_str() );
    }
    return 0;
}