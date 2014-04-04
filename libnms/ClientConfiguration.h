#ifndef _CLIENT_CONFIGURATION_H_
#define _CLIENT_CONFIGURATION_H_

#include <string>

class ConfigReader;

/**
 * Configuration manager responsible for loading the settings from config file
 */
class ClientConfiguration
{
public:

    /**
     * Constructor. Searches the "well-known" locations for the settings of the client
     * The order is:
     * - the directory where the application started
     * - the user's home directory
     */
    ClientConfiguration();

    /**
     * Destructor
     */
    ~ClientConfiguration();

    /**
     * Constructor. Provided is the configuration file
     */
    ClientConfiguration ( const std::string& directory );

    /**
     * Tells us if this was initialized or not
     */
    bool initialized() const
    {
        return initSuccess;
    }

public:

    /**
     * Returns the IP address of the daemon
     */
    std::string getDaemonIP();

    /**
     * Returns the TCP port of the daemon
     */
    int getDaemonTCPPort();

    /**
     * Returns the dispatcher port on which this client wants to communicate
     */
    int preferredDispatcherPort();

private:

    // the configuration reader
    ConfigReader* cfg;

    // if this was succesfully initialized or not
    bool initSuccess;

};

#endif
