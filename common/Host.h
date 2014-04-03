#ifndef _HOST_H_
#define _HOST_H_

#include "NetworkComponent.h"

#include <string>

using namespace std;

class NetworkAddress;

/**
 * Class representing a host
 */
class Host : public NetworkComponent
{
public:

	/**
	 * Retrieves the local host
	 */
	static Host* localhost();

public:

	/**
	 * Default constructor. 
	 */
	Host();

	/**
	 * Construcotr from the given name
	 */
	Host(string name) ;

	/**
	 * Returns the IP of the host
	 */
	string getIp();

private:

	// the name of the host
	string hostName;

	// the address of the host
	NetworkAddress* address;
};

#endif
