#ifndef _ABSTRACT_CLIENT_H_
#define _ABSTRACT_CLIENT_H_

class AbstractSocket;
class NetworkAddress;

/**
 * This abstract class represents a client which connects to a low level TCP Server. Implementations
 * of this interface must provide the onConnect method, which will deal on its turn with the clients
 * connected to the given server.
 */
class AbstractServerClient
{
public:

	/**
	 * This method is called by the Server when a new client has connected
	 * @param sock - the socket, that was received as a result of the "accept" call
	 * @param addr - the address from where this connection was made
	 */
	virtual bool onConnect(AbstractSocket* sock, NetworkAddress* addr) = 0;
};

#endif
