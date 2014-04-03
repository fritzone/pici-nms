#include "AbstractSocket.h"
#include "NetworkAddress.h"
#include "SocketErrorCodes.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef WIN32
#include <unistd.h>
#endif

/**
 * Closes the socket
 */
bool AbstractSocket::close()
{
	//printf("Trying to close socket [%d]", (int)theSocket);
	closed = true;
	if( 
	#ifdef WIN32 
		closesocket
	#else
		::close
	#endif
		(theSocket) == SOCKET_ERROR )
	{
		populateErrorCode(
		#ifndef WIN32
		SocketErrorCodes::OPERATION_CLOSE
		#endif
		);
		closed = false;
	}
	return closed;
}

/**
 * Sets this socket into a non blocking stage
 */
bool AbstractSocket::setNonBlocking()
{
	//printf("[AbstractSocket::setNonBlocking] socket [%d]\n", (int)theSocket);
DWORD nonblock = 1;
	if(
	#ifdef WIN32
		ioctlsocket
	#else
		::ioctl
	#endif
		(theSocket, FIONBIO, &nonblock) == SOCKET_ERROR)
	{
		populateErrorCode(
		#ifndef WIN32
		SocketErrorCodes::OPERATION_IOCTL
		#endif
		);
		return false;
	}
	return true;
}

/**
 * Sets this socket into a non blocking stage
 */
bool AbstractSocket::setBlocking()
{
DWORD nonblock = 0;
	if(
	#ifdef WIN32
		ioctlsocket
	#else
		::ioctl
	#endif
		(theSocket, FIONBIO, &nonblock) == SOCKET_ERROR)
	{
		populateErrorCode(
		#ifndef WIN32
		SocketErrorCodes::OPERATION_IOCTL
		#endif
		);
		return false;
	}
	return true;
}



