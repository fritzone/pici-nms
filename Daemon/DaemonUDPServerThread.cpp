#include "DaemonUDPServerThread.h"
#include "DaemonMutex.h"
#include "DaemonMessageHandlerThread.h"
#include "Daemon.h"

#include "ThreadedUDPServer.h"
#include "Logger.h"
#include "UDPSocket.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sstream>

using namespace std;

DaemonMutex DaemonUDPServerThread::udpMutex;

/**
 * Constructor
 */
DaemonUDPServerThread::DaemonUDPServerThread(Daemon* dmn) : UDPServerThread(), daemon(dmn)
{

}

/**
 * Processes the work
 */
void* DaemonUDPServerThread::process()
{
NetworkAddress fromAddr;
    while(isAlive())
    {
		LOG("Waiting...");
		if ( udpMutex.lock() != 0 )
		{
			LOG("Could not lock mutex. Client not accepted");
		}
		else
		{
			LOG("Locked");
		string received = server->getSocket()->receive(&fromAddr);
			if (received.length() > 0) //something arrived
			{
			DaemonMessageHandlerThread* dmnmsth = new(std::nothrow) DaemonMessageHandlerThread(daemon);
				if(NULL == dmnmsth)
				{
					LOG_ERR("Not enough memory to create a new DaemonMessageHandlerThread thread");
				}
				else
				{
					LOG_DBG("Handling the message");
					dmnmsth->handleMessage(received, fromAddr);
					LOG_DBG("Waiting for the thread to finish what it's doing");
					dmnmsth->waitToFinish();
					LOG_DBG("Freeing the thread");
					delete dmnmsth;
				}
			}
			LOG("Unlocking");
			udpMutex.unlock();
			LOG("Unlocked");
		}
    }
	return NULL;
}
