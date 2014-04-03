#ifndef _DYNAMIC_CLIENT_INITIALIZER_H_
#define _DYNAMIC_CLIENT_INITIALIZER_H_

#include "AbstractClientInitializer.h"

#include <string>

using namespace std;

class PnmsUDPSocket;
class NetworkAddress;

/**
 * Dynamic initializer for a client
 */
class DynamicClientInitializer : public AbstractClientInitializer
{
public:

	/**
	 * Constructor
	 */
	DynamicClientInitializer();

	/**
	 * Destructor
	 */
	~DynamicClientInitializer();

	/**
	 * Initialize the client and retrieve the client identity
	 */
	virtual bool initializeClient();

private:

	/**
	 * Initialize the UDP socket for this initializer
	 */
	bool setupUdpSocket();

	/**
	 * Sends the UDP message, waits for msec milliseconds before giving up
	 */
	bool sendUdpMessage(int timeoutMsec = 3000);

private:

	// Socket which goes to the Daemon in the dynamic initialization phase in
	PnmsUDPSocket* udpSocket;

	// the address which is prepared for broadcasting
	NetworkAddress* broadcastAddress;

	// the response which is received as a reply to the udp broadcast from the Daemon
	string daemonFirstResponse;
};

#endif
