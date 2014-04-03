#ifndef _NETWORK_ADDRESS_H_
#define _NETWORK_ADDRESS_H_

#ifdef WIN32
	#include <Winsock2.h>
#else
	#include "Win2Lin.h"
#endif

#include <string>

using namespace std;

// the network broadcast address
static const string NETWORK_ADDRESS_BROADCAST = "255.255.255.255";

/**
 * Class representing a network address
 */
class NetworkAddress
{

	friend class AbstractSocket;
	friend class TCPSocket;
	friend class UDPSocket;
	friend class TCPServer;
	friend class BasicServerImpl;

public:

	/**
	 * Creates a new Network address from the given IP, on port 0. Unusable for client/server
	 * operations, work only associated to hosts
	 * @param ip - the IP as a numeric value
	 */
	NetworkAddress(unsigned long ip);
	
	/**
	 * Creates a new Network address from the given IP and the given port
	 * @param ip - the IP as a numeric value
	 * @param port - the port as a numeric value
	 */
	NetworkAddress(unsigned long ip, int port);

	/**
	 * Creates a new network address based on the given hostname and port
	 * @param hostname - can be either the name of a host, or a textual representation of an IP number
	 * @param port - is the port 
	 */
	NetworkAddress(const string& hostname, int port);

	/**
	 * Creates a new network address based on the given hostname and port
	 * @param hostname - can be either the name of a host, or a textual representation of an IP number
	 */
	NetworkAddress(const string& hostname);

	/**
	 * Creates a network address with no assigned data
	 */
	NetworkAddress();

	/**
	 * Sets the port to the new value
	 * @param newPort - the new port where this NetworkAddress will refer to
	 */
	void setPort(int newPort)
	{
		address.sin_port = htons(newPort);
	}

	int getPort() const
	{
		return address.sin_port;
	}

	/**
	 * Returns the IP of the network address as a string
	 */
	string getIp();

public:

	/**
	 * Checks whether the string passed in representing a dotted value IP address is valid or not.
	 */
	static bool validIp(const string& IP);

private:

	// the actual address
	SOCKADDR_IN address;
};

#endif
