#include "TcpSocket.h"
#include "NetworkAddress.h"
#include "SocketErrorCodes.h"

#include <stdlib.h>

/**
 * Constructor
 */
TCPSocket::TCPSocket() : AbstractSocket()
{
	initialized = createSocket();
}

TCPSocket::TCPSocket(SOCKET sock) : AbstractSocket(sock)
{
	initialized = true;
}


TCPSocket::~TCPSocket()
{
	close();
}

/**
 * Creates the actual socket
 */
bool TCPSocket::createSocket()
{
	theSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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
 * Conencts the socket to the given address
 */
bool TCPSocket::connectTo(const NetworkAddress* addrs)
{
	if(connect (theSocket, (SOCKADDR*)&(addrs->address), sizeof(addrs->address)) == SOCKET_ERROR )
	{
		populateErrorCode(
		#ifndef WIN32
		SocketErrorCodes::OPERATION_CONNECT
		#endif
		);
		return false;
	}
	return true;
}

/**
* Receives a string on this socket. Optionally returns the address from where we've read
* @param from - the address from which we've received the string
* @return the received string
*/
string TCPSocket::receive(NetworkAddress* from)
{
//	printf("[TCPSocket::receive] entered on socket [%d]\n", (int)theSocket);
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
	int gotLen = recv(theSocket, buffer, clen - 1, MSG_PEEK);	// firstly just "peek" the message
		if(gotLen == clen - 1)	// filled up all the buffer, so let's suppose more is to come
		{
			clen *= 2;
		char *oldBuffer = buffer;
			buffer = (char*)realloc(buffer, clen);
			if(NULL == buffer)
			{
				//LOG("Not enough memory");
				free(oldBuffer);
				return string ("");
			}
		}
		else
		if(gotLen == SOCKET_ERROR)	// did not receive anything for now
		{
			return string("");
		}
		else	// did not fill up the buffer, so this must be the final message
		{
			recvfrom(theSocket, buffer, gotLen, 0, tempAddr, &addrSize);	// 
			buffer[gotLen] = 0;
			can_go = false;
		}
	}
	//printf("[FIN_RECV] [%s]\n", buffer);

string result (buffer);
	free(buffer);
	return result;
}

/**
 * Sends the given string down the socket
 */
bool TCPSocket::send(const string& data)
{
	return sendWrapper(data.c_str(), data.length());
}

/**
 * Simple wrapper around the send method
 */
bool TCPSocket::sendWrapper(const char *toSend, int len)
{
int sent = -1;
	//printf("\nTCPSocket::sending --[%s]--\n", toSend);
	if( (sent = ::send(theSocket, toSend, len, 0)) == SOCKET_ERROR)
	{
		populateErrorCode(
		#ifndef WIN32
		SocketErrorCodes::OPERATION_SEND
		#endif
		);
		return false;
	}
	return true;
}
