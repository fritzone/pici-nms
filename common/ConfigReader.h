#ifndef _CONFIG_READER_H_
#define _CONFIG_READER_H_

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include <map>
#include <string>

using namespace std;

/**
 * Class responsible for loading the configuration file (daemon.xml) and retrieve the config options from there.
 * This class is a singleton.
 */
class ConfigReader
{

public:

    /**
     * Loads the configuration from the file found in the default locations.
     */
    ConfigReader ( const string& file );

    virtual ~ConfigReader();

    /**
     * Loads the config from the given file. If not found loads the config, from the default locations
     */
    ConfigReader ( const string& file, const string& location );

    /**
     * Loads a given value from the XML. The XML file has a 3 level hierarchy.
     */
    string getValue ( const char* parent, const char* branch, const char* cfgval );

    /**
     * Tells us if the configuration was succesfully loaded or not
     */
    bool configLoaded() const
    {
        return initSuccesful;
    }

private:

    /**
     * Loads the configuration from the given file
     */
    bool loadConfig ( const string& );

    /**
     * provides a config file from the given location.
     */
    string provideConfigFile ( int loc );

private:

    // the config file
    string configFile;

    // the XML doc object
    xmlDocPtr doc;

    // holds the configuration values
    map<string, string> config;

    // whether we could load or not the config file
    bool initSuccesful;

    // the full location of the config file
    string fullPath;

};

#endif
