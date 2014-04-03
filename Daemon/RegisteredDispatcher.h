#ifndef _REGISTERED_DISPATCHER_H_
#define _REGISTERED_DISPATCHER_H_

#include "NetworkAddress.h"

#include <string>
using namespace std;

/**
 * This class is responsible for holding the data of a transporter module
 * such as its type, and the port it has
 */
class RegisteredDispatcher
{
public:
	/**
	 * Creates a new RegisteredDispatcher object
	 */
	RegisteredDispatcher(const string& strip, const string& strport, const string& ssitekey);

	/**
	 * returns the port of the dispatcher
	 */
	int getPort() const
	{
		return port;
	}

	/**
	 * Return the IP
	 */
	string getIp()
	{
		return addr.getIp();
	}

	/**
	 * Pings this dispatcher
	 */
	bool ping();
	
private:

	// the IP of the dispatcher
	NetworkAddress addr;

	// the port of the dispatcher
	int port;

	// the sitekey of the dispatcher
	string sitekey;
};

#endif
