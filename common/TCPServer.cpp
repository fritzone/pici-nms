#include "TCPServer.h"
#include "TcpSocket.h"
#include "NetworkAddress.h"
#include "ClientAcceptor.h"
#include "SocketErrorCodes.h"
#include "Logger.h"

/**
 * Constructor
 */
TCPServer::TCPServer() : BasicServerImpl()
{
	sock = new(std::nothrow) TCPSocket();
	if(NULL == sock)
	{
		LOG_ERR("Not enough memory to create a new TCPSocket");
	}
}

TCPServer::TCPServer(ClientAcceptor* acc) : BasicServerImpl(acc)
{
	sock = new (std::nothrow) TCPSocket();
	if(NULL == sock)
	{
		LOG_ERR("Not enough memory to create a new TCPSocket");
	}
}

/**
 * Puts the server in the listening mode
 */
bool TCPServer::listen(int backlog)
{
	if(NULL == this->sock)
	{
		LOG_ERR("The socket object of this server is NULL");
		return false;
	}
int errCode = ::listen(this->sock->theSocket, backlog);
	if(SOCKET_ERROR == errCode)
	{
		populateErrorCode(
		#ifndef WIN32
		SocketErrorCodes::OPERATION_LISTEN
		#endif
		);
		return false;
	}
	return true;
}

/**
* Returns the socket object of the server
* @return the socket
*/
TCPSocket* TCPServer::getSocket() const
{
	return dynamic_cast<TCPSocket*>(sock);
}
