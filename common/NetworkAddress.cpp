#include "NetworkAddress.h"
#include <iostream>

#include <string.h>

using namespace std;

/**
 * Creates a new Network Address object from the given hostname and the given port
 * @param hostname - either the name of the host, or the IP of the host as string
 * @param port - the port (host byte order, automatically will be converted to network byte order)
 */
NetworkAddress::NetworkAddress(const std::string &hostname, int port)
{
unsigned long ip = inet_addr(hostname.c_str());	// if this was an IP as text
	if(INADDR_NONE == ip && hostname!= "255.255.255.255")						// if no address and no broadcast
	{
	hostent* host = gethostbyname(hostname.c_str());	// try to fetch the host
		//cout << "Host="<<host->h_addr_list[0]<<endl;
		ip = inet_addr(host->h_addr_list[0]);			// and verify its first address
		if(INADDR_NONE == ip)							// and if still nothing ...
		{
			ip = 0;										// set the IP to 0
		}
	}
	
	//cout << "New network address:"<<hostname<< "("<<ip<<")"<<endl;
	address.sin_addr.s_addr = ip;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);	
}

NetworkAddress::NetworkAddress(const std::string &hostname)
{
unsigned long ip = inet_addr(hostname.c_str());	// if this was an IP as text
	if(INADDR_NONE == ip && hostname!= "255.255.255.255")						// if no address and no broadcast
	{
	hostent* host = gethostbyname(hostname.c_str());	// try to fetch the host
		//cout << "Host="<<host->h_addr_list[0]<<endl;
		ip = inet_addr(host->h_addr_list[0]);			// and verify its first address
		if(INADDR_NONE == ip)							// and if still nothing ...
		{
			ip = 0;										// set the IP to 0
		}
	}
	
	//cout << "New network address:"<<hostname<< "("<<ip<<")"<<endl;
	address.sin_addr.s_addr = ip;
	address.sin_family = AF_INET;
	address.sin_port = htons(0);	
}


/**
 * Creates a new Network address from the given IP and the given port
 * @param ip - the IP as a numeric value
 * @param port - the port as a numeric value
 */
NetworkAddress::NetworkAddress(unsigned long ip, int port)
{
	address.sin_addr.s_addr = ip;
	address.sin_port = htons(port);
	address.sin_family = AF_INET;
}

/**
 * Creates a new Network address from the given IP and the given port
 * @param ip - the IP as a numeric value
 */
NetworkAddress::NetworkAddress(unsigned long ip)
{
	address.sin_addr.s_addr = ip;
	address.sin_port = htons(0);
	address.sin_family = AF_INET;
}



/**
 * Creates a network address with no assigned data, sets everything to zero.
 */
NetworkAddress::NetworkAddress()
{
	memset(&address, 0, sizeof(address));
}

string NetworkAddress::getIp()
{
char *ip;
	ip = inet_ntoa(address.sin_addr);
	return string(ip);
}

/**
 * TODO: Implement
 */
bool NetworkAddress::validIp(const std::string &IP)
{
	return true;
}