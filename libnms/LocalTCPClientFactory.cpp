#include "LocalTCPClientFactory.h"
#include "LocalTCPClient.h"
#include "TransporterImpl.h"
#include "Logger.h"

LocalTCPClientFactory::LocalTCPClientFactory(TransporterImpl* timpl) : transp(timpl)
{
}

AbstractServerClient* LocalTCPClientFactory::newObject()
{
LocalTCPClient* ltcpc = new(std::nothrow) LocalTCPClient(transp);
	if(NULL == ltcpc)
	{
		LOG_ERR("Not enough memory to create a new client");
		return NULL;
	}
	return ltcpc;
}
