#ifndef _LOCAL_TCP_CLIENT_FACTORY_H_
#define _LOCAL_TCP_CLIENT_FACTORY_H_

#include "AbstractServerClientFactory.h"

class AbstractServerClient;
class TransporterImpl;

/**
 * Factory class fro creating local TCP clients
 */
class LocalTCPClientFactory : public AbstractServerClientFactory
{
public:

	/**
	 * Constructor
	 */
	LocalTCPClientFactory(TransporterImpl* timpl);

	/**
	 * Create a new object
	 */
	virtual AbstractServerClient* newObject();

private:

	TransporterImpl* transp;
};

#endif
