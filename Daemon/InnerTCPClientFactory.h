#ifndef _INNER_TCP_CLIENT_FACTORY_H_
#define _INNER_TCP_CLIENT_FACTORY_H_

#include "AbstractServerClientFactory.h"

class Daemon;

/**
 * Creates InnerTCPClient objects
 */
class InnerTCPClientFactory : public AbstractServerClientFactory
{
public:

	/**
	 * Constructor
	 */
	InnerTCPClientFactory(Daemon* dmn);

	/**
	 * Creates a new object
	 */
	virtual AbstractServerClient* newObject();

private:

	Daemon* daemon;
};

#endif
