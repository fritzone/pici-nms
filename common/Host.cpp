#include "Host.h"
#include "NetworkAddress.h"
#include "Logger.h"
#include <stdio.h>
#include <unistd.h>
#include <sstream>

using namespace std;

/**
 * Creates an empty host, default values
 */
Host::Host() : NetworkComponent(), hostName ( "" ), address ( NULL )
{
}

/**
 * Constructor. Creates a host object from the given host name
 */
Host::Host ( string name ) : NetworkComponent(), hostName ( name )
{
    stringstream ss;
    HOSTENT* host = gethostbyname ( hostName.c_str() );
    char hostIp[256];
#ifdef _WIN32
#ifdef sprintf_s
    sprintf_s
#else
    sprintf
#endif
#else
    snprintf
#endif
    ( hostIp,

#ifdef _WIN32
#ifdef sprintf_s
      255,
#endif
#else
      255,
#endif
      "%i.%i.%i.%i", ( unsigned char ) host->h_addr_list[0][0], ( unsigned char ) host->h_addr_list[0][1],
      ( unsigned char ) host->h_addr_list[0][2], ( unsigned char ) host->h_addr_list[0][3] );
    unsigned long addrs = inet_addr ( hostIp );
    address = new ( std::nothrow ) NetworkAddress ( addrs );
    if ( NULL == address )
    {
        LOG_ERR ( "Not enough memory to create a new NetworkAddress" );
    }
}

/**
 * Retrieves the localhost
 */
Host* Host::localhost()
{
    char curhost[256];
    gethostname ( curhost, 255 );
    Host* newHost = new ( std::nothrow ) Host ( curhost );
    if ( NULL == newHost )
    {
        LOG_ERR ( "Not enough memory to create a new host" );
    }
    return newHost;
}

string Host::getIp()
{
    return address->getIp();
}
