#include "DynamicClientInitializer.h"
#include "PnmsUDPSocket.h"
#include "CommandNMS_INIT.h"
#include "ClientConfiguration.h"

#include "NetworkAddress.h"
#include "constants.h"
#include "Logger.h"
#include "Thread.h"

/**
 * Constructor
 */
DynamicClientInitializer::DynamicClientInitializer() : udpSocket(NULL), broadcastAddress(NULL), daemonFirstResponse("")
{
	LOG_DBG("DynamicclientInitializer is constructing");
}

/**
 * Destructor
 */
DynamicClientInitializer::~DynamicClientInitializer()
{
	if(udpSocket) delete udpSocket;
	if(broadcastAddress) delete broadcastAddress;
}

/**
 * Creates an UDP socket to send to the daemon the message
 */
bool DynamicClientInitializer::setupUdpSocket()
{
	// creating the socket to broadcast to the daemon on the network
	udpSocket = new(std::nothrow) PnmsUDPSocket();
	if(NULL == udpSocket)
	{
		LOG_ERR("Not enough memory to create a UDP socket");
		return false;
	}
	if(!udpSocket->isInitialized())
	{
		LOG("Cannot create socket to Daemon " + udpSocket->getError());
		delete udpSocket;
		forceFail();
		return false;
	}

	// preparing the socket for UDP broadcasting
BOOL bBroadcast = TRUE;

	if( !udpSocket->enableBroadcast() ) 
	{
		LOG("Cannot enable broadcast mode " + udpSocket->getError());
		delete udpSocket;
		forceFail(); 
		return false;
	}

	// connecting the socket to the broadcast address
	broadcastAddress = new(std::nothrow) NetworkAddress(NETWORK_ADDRESS_BROADCAST, DAEMON_PORT);
	if(NULL == broadcastAddress)
	{
		LOG("Not enough memory to create a broadcast address");
		delete udpSocket;
		forceFail();
		return false;
	}
	udpSocket->connectTo(broadcastAddress);
	

	return  true;
}

/**
 * Initializes this as a dynamic client
 */
bool DynamicClientInitializer::initializeClient()
{
	if(!basicInit())
	{
		LOG_ERR("Basic initialization failed");
		return false;
	}

	LOG("Basic initialization done");

	// Second: Creating an UDP socket, to send the NMS_INIT broadcast
	if(!setupUdpSocket()) 
	{
		return false;
	}

	// Send the NMS_INIT message, and wait for an acceptable response, or the occurrence of a timeout

	LOG("Sending UDP");
	if(!sendUdpMessage())
	{
		if(getLastErrorCode() != ErrorCodes::TIMEOUT)
		{
			LOG("Cannot send UDP message");
			setLastErrorCode(888);
		}
		else
		if(getLastErrorCode() == ErrorCodes::TIMEOUT)
		{
			LOG("Timeout ...");
		}
		return false;
	}

	if(daemonFirstResponse == COMMAND_NOINIT)	// NOINIT ... unknown reasons
	{			
		LOG("Not a valid response from daemon");
		return false;
	}

	if(!analyzeResponse(daemonFirstResponse.c_str()))
	{
		LOG("Could not analyze the daemons response");
		return false;
	}

	return true;
}



/**
 * Send the UDP message to be received by the daemon                                                                     
 */
bool DynamicClientInitializer::sendUdpMessage(int timeoutMsec)
{
CommandNMS_INIT* cmdInit = new(std::nothrow) CommandNMS_INIT(CONFIG_DISPATCHER_PROTOCOL, 7566);
	if(NULL == cmdInit)
	{
		LOG_ERR("Not enough memory to create the NMS_INIT command");
		setLastErrorCode(ErrorCodes::NOT_ENOUGH_MEMORY);
		return false;
	}

	if(!udpSocket->send(cmdInit))	// sending the broadcast message
	{
		LOG_ERR("UDP broadcast: sendto failed" + udpSocket->getError());
		setLastErrorCode(udpSocket->getErrorCode());
		delete cmdInit;
		return false;
	}

	Thread::suspendCurrent(100);

	if(!udpSocket->setNonBlocking())
	{
		LOG_ERR("Cannot set the UDP socket to non-blocking");
		delete cmdInit;
		setLastErrorCode(ErrorCodes::INTERNAL_ERROR);
		return false;
	}

NetworkAddress naddrResponse;
	daemonFirstResponse = COMMAND_NOINIT;
time_t startTime,nowTime;
	time(&startTime);
	while(true)
	{

		Thread::suspendCurrent(100);
		
	string broadcastReply = udpSocket->receive(&naddrResponse);		
		if( broadcastReply.length() > 0 ) 
		{
			if(!udpSocket->close())
			{
				LOG_ERR("Error while closing a socket");
			}
			daemonFirstResponse = broadcastReply;
			delete cmdInit;
			return true;
		}
		else
		{
			time(&nowTime);
			if(nowTime - startTime >= timeoutMsec)
			{
				udpSocket->close();
				setLastErrorCode(ErrorCodes::TIMEOUT);
				delete cmdInit;
				return false;
			}
		}
	}
	LOG_ERR("Reached to an invalid location in the code");
	delete cmdInit;
	return false;
}
