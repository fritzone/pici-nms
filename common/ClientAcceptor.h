#ifndef _CLIENT_ACCEPTOR_H_
#define _CLIENT_ACCEPTOR_H_

class AbstractServerClient;

#include "AbstractServerClientFactory.h"

/**
 * Interface responsible for handling clients connected to a Server. Every time the server has 'accept'-ed 
 * a new client, the onConnect method of the client assigned to this class will get called.
 * This ensures a mechanism which is flexible enough to exchange clients under a server.
 */
class ClientAcceptor
{
public:

	/**
	 * Constructor, gets a client as parameter.
	 * @param client - the client of this acceptor
	 */
	ClientAcceptor(AbstractServerClientFactory* clientf) : clientFactory(clientf)
	{
	}

	/**
	 * This will return the client connected to this ClientAcceptor
	 * @return the client of this acceptor
	 */
	AbstractServerClientFactory* getClient() const
	{
		return clientFactory;
	}

private:

	// this is the client of the acceptor
	AbstractServerClientFactory* clientFactory;
};

#endif
