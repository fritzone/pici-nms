#include "Logger.h"
#include "UDPServerThread.h"
#include "ThreadedUDPServer.h"
#include "NetworkAddress.h"
#include "UDPSocket.h"
#include "ClientAcceptor.h"
#include "AbstractServerClient.h"

#ifdef _WIN32
#include <WinSock2.h>
#endif

void UDPServerThread::setServer ( ThreadedUDPServer* srv )
{
    server = srv;
}
