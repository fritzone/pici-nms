#include "Daemon.h"
#include "DaemonMutex.h"
#include "DaemonUDPServerThread.h"
#include "DaemonInnerTCPServerThread.h"
#include "InnerTCPClientFactory.h"
#include "RegisteredDispatcher.h"
#include "DaemonPingerThread.h"

#include "NetworkAddress.h"
#include "ThreadedUDPServer.h"
#include "Logger.h"
#include "ThreadedTCPServer.h"
#include "ClientAcceptor.h"
#include "ConfigReader.h"

#ifdef _WIN32
	#include "RegConfReader.h"
#else
	#include <sys/ioctl.h>
	#include <net/if.h>
	#include <netinet/in.h>
	#include <netinet/ether.h>
	#include <stdio.h>
	#include <arpa/inet.h>
	#include <string.h>
#endif

#include <new>

int Daemon::dynamicHostCount = 0;
int Daemon::dispatcherIdCount = 0;

/**
 * Constructor. Creates a new object
 */
Daemon::Daemon() :	udpDaemonPort(0), tcpInnerDaemonPort(0), udpserv(NULL), udpNetAddr(NULL), dups(NULL),
					innerTCPServer(NULL), daemonInnerThread(NULL), innerTcpClFac(NULL), ca(NULL), innerIP("")

{
	LOG_DBG("Daemon constructor");
}

/**
 * Daemon Destructor.
 */
Daemon::~Daemon()
{
	LOG_DBG("Daemon object being destroyed");

#ifdef _WIN32
	WSACleanup();
#endif

	if(udpserv != NULL) delete udpserv;
	if(udpNetAddr != NULL) delete udpNetAddr;
	if(dups != NULL) delete dups;
	if(innerTCPServer != NULL) delete innerTCPServer;
	if(daemonInnerThread != NULL) delete daemonInnerThread;
	if(innerTcpClFac != NULL) delete innerTcpClFac;
	if(ca != NULL) delete ca;

}

/**
 * Initializes the network interfaces, matching them against the config file
 */
bool Daemon::initializeInterfaces()
{
bool innerFound = false;
#ifdef _WIN32	
char hostName[256];
	gethostname(hostName, 255);
	printf("Running on host:%s\n", hostName);
hostent* hostPtr;
	hostPtr = gethostbyname(hostName);
char** pptr = hostPtr->h_addr_list;
	while(*pptr)
	{
	char cIP[256];
		sprintf(cIP, "%d.%d.%d.%d", (unsigned char)(*(*pptr)), (unsigned char)(*(*pptr+1)), (unsigned char)(*(*pptr+2)), (unsigned char)(*(*pptr+3)));
		printf("Found interface: %s\n", cIP);
		if(inet_addr(cIP) == inet_addr(innerIP.c_str()))
		{
			printf(" >>> Found inner network:%s\n", cIP);
			innerFound = true;
		}
		pptr ++;
	}

#else

	// Get a socket handle. 
int sck = socket(AF_INET, SOCK_DGRAM, 0);
	if(sck < 0)
	{
		LOG_ERR("Cannot create a temporary socket");
		return false;
	}

	// Query available interfaces.
char buf[1024];
struct ifconf ifc;
struct ifreq *ifr;

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
	if(ioctl(sck, SIOCGIFCONF, &ifc) < 0)
	{
		LOG_ERR("Error in ioctl(SIOCGIFCONF)");
		return false;
	}

	ifr         = ifc.ifc_req;
int nInterfaces = ifc.ifc_len / sizeof(struct ifreq);
	for(int i = 0; i < nInterfaces; i++)
	{
	struct ifreq *item = &ifr[i];
	char tmpIp[128];
		snprintf(tmpIp, 128, "%s", inet_ntoa(((struct sockaddr_in *)&item->ifr_addr)->sin_addr));
		if(!strcmp(tmpIp, innerIP.c_str()))
		{		
			innerFound = true;
		}
	}
#endif

	return innerFound;
}

/**
 * Initialize the winsock
 */
#ifdef WIN32
bool Daemon::initWinsock()
{
WSADATA wsaData;
int startupCode = WSAStartup (MAKEWORD (2, 2), &wsaData);
	if (SOCKET_ERROR == startupCode)
	{
		char s[256];
		sprintf_s (s, 256, "WSAStartup Failed. Code:%d", WSAGetLastError ());
		LOG (s);
		return false;
	}
	return true;
}
#endif

/**
 * Loads the daemon configuration file
 */
bool Daemon::loadConfig()
{
#ifdef WIN32
	std::string confLocation = RegConfReader::getConfigFileLocation("Daemon");
	ConfigReader cfg ("daemon.xml", confLocation);
#else
	ConfigReader cfg ("daemon.xml");	// deleted a few lines below
#endif

	if(!cfg.configLoaded())
	{
		LOG("Config file was not parsed succesfully, leaving");
		return false;
	}

string strUdpDaemonPort = cfg.getValue("socket", "socketinfo", "UDP_DAEMON_PORT");
string stcpDaemonPort = cfg.getValue("socket", "socketinfo", "TCP_DAEMON_PORT");
	LOG(stcpDaemonPort);

	if(strUdpDaemonPort.length() == 0)
	{
		LOG("UDP port has a strange value");
		return false;
	}

	if(stcpDaemonPort.length() == 0) 
	{
		LOG("TCP port has a strange value");
		return false;
	}

	udpDaemonPort = atoi(strUdpDaemonPort.c_str());
	tcpInnerDaemonPort = atoi(stcpDaemonPort.c_str());

	innerIP = cfg.getValue("network", "inner", "IP");
	LOG(innerIP);

	return true;
}

/**
 * Creates the UDP Server of the application
 */
bool Daemon::createUDPServer()
{
	LOG("Creating udp serv");
	dups = new(std::nothrow) DaemonUDPServerThread(this);
	if(NULL == dups)
	{
		LOG_ERR("Could not create UDP server's thread");
		return false;
	}

	udpserv = new(std::nothrow) ThreadedUDPServer(dups);
	if(NULL == udpserv)
	{
		LOG_ERR("Could not create UDP server");
		delete dups;
		dups = NULL;
		return false;
	}

	udpNetAddr = new(std::nothrow) NetworkAddress(htonl (INADDR_ANY), udpDaemonPort);
	if(NULL == udpNetAddr)
	{
		LOG_ERR("Could not create network address");
		delete dups;
		dups = NULL;
		delete udpserv;
		udpserv = NULL;
		return false;
	}

	if(!udpserv->bind(udpNetAddr))
	{
		LOG_ERR("Cannot bind server");

		delete dups;
		dups = NULL;

		delete udpserv;
		udpserv = NULL;

		delete udpNetAddr;
		udpNetAddr = NULL;

		return false;
	}

	return true;
}

/**
 * Creates the inner TCP Server on the innerIP as specified in the config file
 */
bool Daemon::createInnerTCPServer()
{
	daemonInnerThread = new (std::nothrow) DaemonInnerTCPServerThread(this);
	if(NULL == daemonInnerThread)
	{
		LOG_ERR("Not enough memory to create a thread for the inner TCP Server");
		return false;
	}

	innerTCPServer = new(std::nothrow) ThreadedTCPServer(daemonInnerThread);
	if(NULL == innerTCPServer)
	{
		LOG_ERR("Not enough memory to create a new ThreadedTCPServer");

		delete daemonInnerThread;
		daemonInnerThread = NULL;

		return false;
	}

	innerTcpClFac = new(std::nothrow) InnerTCPClientFactory(this);
	if(NULL == innerTcpClFac)
	{
		LOG_ERR("Not enough memory to create a new InnerTCPClientFactory");

		delete innerTCPServer;
		innerTCPServer = NULL;

		delete daemonInnerThread;		
		daemonInnerThread = NULL;

		return false;
	}

	ca = new(std::nothrow) ClientAcceptor(innerTcpClFac);
	if(NULL == ca)
	{
		LOG_ERR("Not enough memory to create a new ClientAcceptor");

		delete innerTcpClFac;
		innerTcpClFac = NULL;

		delete innerTCPServer;
		innerTCPServer = NULL;

		delete daemonInnerThread;
		daemonInnerThread = NULL;

		return false;
	}

	innerTCPServer->setAcceptor(ca);

NetworkAddress na(innerIP, tcpInnerDaemonPort);
	if(!innerTCPServer->bind(&na))
	{
		LOG_ERR("Cannot bind TCP server");
		LOG_ERR(innerTCPServer->getError());

		delete innerTcpClFac;
		innerTcpClFac = NULL;

		delete innerTCPServer;
		innerTCPServer = NULL;

		delete daemonInnerThread;
		daemonInnerThread = NULL;
		return false;
	}

	if(!innerTCPServer->listen())
	{
		LOG_ERR("Local TCP server is not listening");

		delete innerTcpClFac;
		innerTcpClFac = NULL;

		delete innerTCPServer;
		innerTCPServer = NULL;

		delete daemonInnerThread;
		daemonInnerThread = NULL;

		return false;
	}

	return true;
}

/**
 * Loads the configuration, Starts the windows sockets and creates the daemon socket
 */
bool Daemon::startup()
{
	pinger = new DaemonPingerThread(this);
	if(!pinger->start())
	{
	    printf("Cannot start the pinger thread ,,,\n");
	}
	
    // Parse xml file to get the config elements.
	if(!loadConfig())
	{
		LOG_ERR("Configuration was not loaded succesfully");
		return false;
	}

    //Starting the Windows SOCKETS in case of running on Windows
#ifdef WIN32
	if(!initWinsock())
	{
		LOG_ERR("Cannot startup WinSock");
		return false;
	}
#endif

	if(!initializeInterfaces())
	{
		LOG_ERR("Network Interfaces were not initialized succesfully");
		return false;
	}

	// create the UDP Server
	if(!createUDPServer())
	{
		LOG_ERR("UDP Server creation failure");
		return false;
	}

	if(!udpserv->start())
	{
		LOG_ERR("Cannot start UDP server");

		delete dups;
		dups = NULL;

		delete udpserv;
		udpserv = NULL;

		delete udpNetAddr;
		udpNetAddr = NULL;

		return false;
	}

	if(!createInnerTCPServer())
	{
		LOG_ERR("Cannot create Inner TCP Server");
		// stop the UDP server
		udpserv->stop();
		
		delete dups;
		dups = NULL;

		delete udpserv;
		udpserv = NULL;

		delete udpNetAddr;
		udpNetAddr = NULL;

		return false;
	}

	if(!innerTCPServer->start())
	{
		LOG_ERR("Cannot start Inner TCP Server");
		// Stop the UDP
		udpserv->stop();

		delete dups;
		dups = NULL;

		delete udpserv;
		udpserv = NULL;

		delete udpNetAddr;
		udpNetAddr = NULL;

		// free the stuff if the TCP Server
		delete innerTcpClFac;
		innerTcpClFac = NULL;

		delete innerTCPServer;
		innerTCPServer = NULL;

		delete daemonInnerThread;
		daemonInnerThread = NULL;

		return false;
	}


    return true;
}

/**
 * TODO: Implement
 */
bool Daemon::isValidSitekey(const std::string &sitekeky, const NetworkAddress *from) const
{
	return true;
}

bool Daemon::addDispatcher(const string& ip, const string& port, const string& sitekey)
{
	for(int i=0 ;i < dispatchers.size(); i++)
	{
		if(dispatchers[i]->getIp() == ip && dispatchers[i]->getPort() == atoi(port.c_str()))
		{
			return false;
		}
	}
RegisteredDispatcher* regd = new RegisteredDispatcher(ip, port, sitekey);

	addDispatcher(regd);
	return true;
}

void Daemon::removeDispatcher(RegisteredDispatcher *rd)
{
vector<RegisteredDispatcher*>::iterator it = dispatchers.begin();
	while(*it != rd)
	{
		it ++;
	}
	if(it == dispatchers.end()) return;
	dispatchers.erase(it);
}


