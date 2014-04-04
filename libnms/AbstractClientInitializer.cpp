#include "AbstractClientInitializer.h"
#include "ClientIdentity.h"

#include "Logger.h"
#include "constants.h"
#include "NetworkAddress.h"

#include <string.h>
#include <stdlib.h>

/**
 * Constructor
 */
AbstractClientInitializer::AbstractClientInitializer() : AbstractInitializer(), startupErrorCode ( -1 )
{
}

/**
 * Performs some basic initialization
 */
bool AbstractClientInitializer::basicInit()
{

    LOG ( "Initializing basic communication system" );
    forceSuccess();

#ifdef _WIN32
    // First: Initializing the Winsock
    if ( !initWinsock() )
    {
        return false;
    }
#endif

    return true;
}

#ifdef _WIN32

/**
 * Initializes the Winsock interface
 */
bool AbstractClientInitializer::initWinsock()
{
    WSADATA wsaData;
    startupErrorCode = WSAStartup ( MAKEWORD ( 2, 2 ), &wsaData );
    setLastErrorCode ( startupErrorCode );
    if ( startupErrorCode != 0 )
    {
        //failed in initializing the windows sockets, simply flip the state of initialized
        LOG_ERR ( "WSAStartup failed", getLastErrorCode() );
        forceFail();
        return false;
    }
    return true;
}

#endif // _WIN32

/**
 * The method analyzes the response from the daemon, and initializes base members of
 * communication
 */
bool AbstractClientInitializer::analyzeResponse ( const char* response )
{
    // we should check if NMS_OK arrives firstly

    // the IP address of the daemon
    char* transporterIp = NULL;

    // the port of the daemon
    int transporterPort = 0;
    // now we have to retrieve the necessary information from the response,
    // such as: IP Address, Port
    if ( strncmp ( response, COMMAND_NMS_OK, strlen ( COMMAND_NMS_OK ) ) )
    {
        setLastErrorCode ( ErrorCodes::MALFORMED_RESPONSE );
        return false;
    }
    const char* ipPos = strchr ( response, ':' );
    if ( ipPos == NULL )
    {
        setLastErrorCode ( ErrorCodes::MALFORMED_RESPONSE );
        return false;
    }
    ipPos++;    // now IP Pos points to the real IP
    const char* portPos = strchr ( ipPos, ':' ); //the position of the port
    if ( portPos == NULL )
    {
        setLastErrorCode ( ErrorCodes::MALFORMED_RESPONSE );
        return false;
    }
    int ipLen = portPos - ipPos;
    transporterIp = new ( std::nothrow ) char [ipLen + 1];
    if ( NULL == transporterIp )
    {
        setLastErrorCode ( ErrorCodes::NOT_ENOUGH_MEMORY );
        return false;
    }
    strncpy ( transporterIp, ipPos, ipLen );
    transporterIp[ipLen] = 0;   //here we have the daemon's IP address
    portPos ++;                 //jumping to the next position, where the port begins
    transporterPort = atoi ( portPos ); //here we have the daemons port
    // here we extract the Client identifier of this object
    const char* hashPos = strchr ( response, COMMAND_SEPARATOR1 );
    if ( hashPos == NULL )
    {
        setLastErrorCode ( ErrorCodes::MALFORMED_RESPONSE );
        return false;
    }
    const char* atPos = strchr ( response, '@' );
    if ( atPos == NULL )
    {
        setLastErrorCode ( ErrorCodes::MALFORMED_RESPONSE );
        return false;
    }
    int idLen = atPos - hashPos;
    char* temp = new ( std::nothrow ) char[idLen + 1];
    if ( NULL == temp )
    {
        delete[] transporterIp;
        setLastErrorCode ( ErrorCodes::NOT_ENOUGH_MEMORY );
        return false;
    }
    strncpy ( temp, hashPos + 1, idLen - 1 );
    temp[idLen - 1] = 0;

    int clientNumber = atoi ( temp );
    cid = new ( std::nothrow ) ClientIdentity ( clientNumber );
    if ( NULL == cid )
    {
        setLastErrorCode ( ErrorCodes::NOT_ENOUGH_MEMORY );
        delete[] temp;
        delete[] transporterIp;
        return false;
    }
    dispatcherAddress = new ( std::nothrow ) NetworkAddress ( transporterIp, transporterPort );
    if ( NULL == dispatcherAddress )
    {
        delete [] temp;
        delete [] transporterIp;
        delete cid;
        setLastErrorCode ( ErrorCodes::NOT_ENOUGH_MEMORY );
        return false;
    }
    delete [] temp;
    delete [] transporterIp;

    return true;
}

/**
 * Retrieves the identity of the client
 */
ClientIdentity* AbstractClientInitializer::retrieveClientIdentity()
{
    return cid;
}

NetworkAddress* AbstractClientInitializer::getDispatcherAddress()
{
    return dispatcherAddress;
}
