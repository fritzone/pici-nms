#ifndef _ABSTRACT_SERVER_CLIENT_FACTORY_H_
#define _ABSTRACT_SERVER_CLIENT_FACTORY_H_

class AbstractServerClient;

/**
 * Factory method for creating Abstract Clients
 */
class AbstractServerClientFactory
{
public:

	/**
	 * Creates a new object
	 */
	virtual AbstractServerClient* newObject() = 0;

    virtual ~AbstractServerClientFactory() {}

};

#endif
