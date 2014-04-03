#ifndef _BASIC_SERVER_IMPL_H_
#define _BASIC_SERVER_IMPL_H_

#include "AbstractServer.h"

class NetworkAddress;
class AbstractSocket;

/**
 * Very basic server implementation
 */
class BasicServerImpl :  public AbstractServer
{
public:

	/**
	 * Constructor
	 */
	BasicServerImpl();

	/**
	 * Constructor with a client acceptor
	 */
	BasicServerImpl(ClientAcceptor* acc);

	/**
	 * Binds the server to the given address
	 * @param addr - the address which will be used for this server
	 * @return true in case of success, false in case of failure
	 */
	bool bind(NetworkAddress* addr);

protected:

	// the socket which is used by this Server
	AbstractSocket*  sock;

	// the address to which this server is bound
	NetworkAddress* address;
};

#endif

