#include "UDPSocket.h"
#include "NetworkAddress.h"
#include "SocketErrorCodes.h"

#include <stdlib.h>

/**
 * Constructor
 */
UDPSocket::UDPSocket() : AbstractSocket()
{
	initialized = createSocket();
}

/**
 * Creates the actual socket
 */
bool UDPSocket::createSocket()
{
	theSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(INVALID_SOCKET == theSocket)
	{
		populateErrorCode(
		#ifndef WIN32
		SocketErrorCodes::OPERATION_SOCKET
		#endif
		);
		return false;
	}
	return true;
}

/**
 * Enabled the broadcasting on the socket
 */
bool UDPSocket::enableBroadcast()
{
	clearError();
BOOL broadcast = TRUE;
	if( setsockopt(theSocket, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(BOOL)) == SOCKET_ERROR ) 
	{
		populateErrorCode(
		#ifndef WIN32
		SocketErrorCodes::OPERATION_SETSOCKOPT
		#endif
		);
		return false;
	}
	return true;
}


/**
 * Connects this socket to the given address
 */
bool UDPSocket::connectTo(const NetworkAddress* addrs)
{
	naddress = const_cast<NetworkAddress*>(addrs);
	return true;
}

/**
 * Receives a string through this socket. Tries to determine how many bytes to allocate 
 * for the whole process, and returns a string containing the laoded bytes.
 * It has a limit of 65537 bytes to allocate
 */
string UDPSocket::receive(NetworkAddress* from)
{
int clen = 1024;
int max_accepted = 65537;
char* buffer = (char*)malloc(clen * sizeof(char));	// initial buffer
	if(NULL == buffer)
	{
		return string ("");
	}
int can_go = true;
SOCKADDR* tempAddr = from ? (SOCKADDR*)&from->address : (SOCKADDR*)NULL;
#ifdef WIN32
int 
#else
socklen_t
#endif
	addrSize = sizeof(SOCKADDR);
	while(can_go && clen < max_accepted)
	{
		//printf("U.");
	int gotLen = recvfrom(theSocket, buffer, clen - 1, MSG_PEEK, tempAddr, &addrSize);	// firstly just "peek" the message
		if(gotLen == clen - 1)	// filled up all the buffer, so let's suppose more is to come
		{
			clen *= 2;
		char* oldBuffer = buffer;
			buffer = (char*)realloc(buffer, clen);
			if(NULL == buffer)
			{
				free(oldBuffer);
				return string ("");
			}
		}
		else
		if(gotLen == SOCKET_ERROR)	// did not receive anything for now
		{
			return "";
		}
		else	// did not fill up the buffer, so this must be the final message
		{
			recvfrom(theSocket, buffer, gotLen, 0, tempAddr, &addrSize);	// 
			buffer[gotLen] = 0;
			can_go = false;
		}
	}
string result (buffer);
	free(buffer);
	return result;
}


/**
 * Sends the given string to the network address connected to this socket
 */
bool UDPSocket::send(const std::string & data)
{
int sent = -1;
	//puts(data.c_str());
	if((sent = sendto(theSocket, data.c_str(), data.length(), 0, (SOCKADDR*)&(naddress->address), sizeof(naddress->address))) == SOCKET_ERROR) 
	{
		populateErrorCode(
		#ifndef WIN32
		SocketErrorCodes::OPERATION_SENDTO
		#endif
		);
		return false;
	}
	return true;
}
