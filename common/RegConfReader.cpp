#ifdef _WIN32

#include "RegConfReader.h"

#ifdef DISPATCHER
#include "local.h"
#else
#include "Logger.h"
#endif

#include <windows.h>

/**
 * Read the location of the config file from the registry
 */
string RegConfReader::getConfigFileLocation ( const string& comp )
{
    HKEY regKey;
    DWORD bufLen = 1024;
    LONG retv;
    char configFile[1024];

    retv = RegOpenKeyEx ( HKEY_LOCAL_MACHINE, string ( string ( "SOFTWARE\\Pici-NMS\\" ) + comp ).c_str(), 0, KEY_QUERY_VALUE, &regKey );
    if ( retv != ERROR_SUCCESS )
    {
        LOG ( "Cannot load the registry key for the config file location" );
        return "";
    }

    retv = RegQueryValueEx ( regKey, "configdir", NULL, NULL, ( LPBYTE ) configFile, &bufLen );
    if ( retv != ERROR_SUCCESS )
    {
        RegCloseKey ( regKey );
        LOG ( "Cannot retrieve the config file location from the registry" );
        return "";
    }

#ifdef DISPATCHER
    LOG ( "Config file found at:%s", configFile );
#else
    LOG ( "Config file location found at:" );
    LOG ( configFile );
#endif
    RegCloseKey ( regKey );
    return string ( configFile );
}

#endif
