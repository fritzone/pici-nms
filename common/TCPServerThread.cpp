#include "TCPServerThread.h"
#include "ThreadedTCPServer.h"

#include "Logger.h"
#include "NetworkAddress.h"
#include "TcpSocket.h"
#include "SocketErrorCodes.h"
#include "ClientAcceptor.h"
#include "AbstractServerClient.h"

#ifdef WIN32
	#include <WinSock2.h>
	#define socklen_t int
#else
	#ifdef LINUX
		#include "Win2Lin.h"
	#endif
#endif

void TCPServerThread::setServer(ThreadedTCPServer* srv)
{
	server = srv;
	alive = true;
}


void* TCPServerThread::process()
{
socklen_t addrLen = sizeof(SOCKADDR_IN);
	while(true && alive)
	{
		Thread::suspendCurrent(100);
	SOCKADDR_IN fromAddr;
	SOCKET socketFromDispatcher = accept(server->getSocket()->getOSSocket(), (SOCKADDR*)&fromAddr, &addrLen);
		if(socketFromDispatcher == INVALID_SOCKET)
		{
			#ifdef WIN32
			LOG(SocketErrorCodes::getErrorDescription(WSAGetLastError()));
			#endif
			LOG("Invalid Socket from Dispatcher");
		}
		else
		{
		TCPSocket* sock = NULL;					// deleted by the clients
		NetworkAddress* addr = NULL;			// deleted by the clients
			try
			{
				sock = new(std::nothrow) TCPSocket(socketFromDispatcher);		// will be deleted in the Connection::~Connection (for the clients)
				if(NULL == sock)
				{
					LOG_ERR("Not enough memory to create a new accepting socket");
					return NULL;
				}

				addr = new(std::nothrow) NetworkAddress(fromAddr.sin_addr.s_addr, fromAddr.sin_port); // this will be deleted in the LocalTCPClient::onConnect, it's not really used (for the clients)
				if(NULL == addr)
				{
					LOG_ERR("Not enough memory to create a new NetworkAddress");
					delete sock;
					return NULL;
				}
				// fetch the acceptor
			ClientAcceptor* acceptor = server->getAcceptor();
				if(NULL == acceptor)
				{
					LOG_ERR("There is no client acceptor associated with the server");
					if(sock) delete sock;
					if(addr) delete addr;
					return NULL;
				}
				// and the acceptors factory
			AbstractServerClientFactory* ascf = acceptor->getClient();
				if(NULL == ascf)
				{
					LOG_ERR("There is no factory associated with the acceptor");
					if(sock) delete sock;
					if(addr) delete addr;
					return NULL;
				}
				// create a new client
			AbstractServerClient* asc = ascf->newObject();
				if(NULL == asc)
				{
					LOG_ERR("Cannot create a new client");
					if(sock) delete sock;
					if(addr) delete addr;
					return NULL;
				}
				asc->onConnect(sock, addr);
			}
			catch(...)
			{
				LOG_ERR("Unknow nexception");
				if(sock) delete sock;
				if(addr) delete addr;
			}
		}
	}
	return NULL;
}


bool TCPServerThread::stop()
{
	alive = false;
	return true;
};
