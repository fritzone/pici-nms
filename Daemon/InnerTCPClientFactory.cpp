#include "InnerTCPClientFactory.h"
#include "InnerTCPClient.h"
#include "Logger.h"

InnerTCPClientFactory::InnerTCPClientFactory(Daemon* dmn):daemon(dmn)
{
}

AbstractServerClient* InnerTCPClientFactory::newObject()
{
InnerTCPClient* itcpc = new(std::nothrow) InnerTCPClient(daemon);
	if(NULL == itcpc)
	{
		LOG_ERR("Not enough memory to create a new InnerTCPClient");
		return NULL;
	}
	return itcpc;
}
