#include "NetworkComponent.h"
#include "SocketErrorCodes.h"

#ifdef WIN32
	#include <WinSock2.h>
#else
	#include <errno.h>
#endif

NetworkComponent::NetworkComponent():initialized(false), errorText(""), errorCode(0)
{
}

void NetworkComponent::populateErrorCode(
#ifndef WIN32
	int reqdOperation
#endif
)
{
#ifdef WIN32
	errorCode = WSAGetLastError();
	errorText = SocketErrorCodes::getErrorDescription(errorCode);
#else
	errorCode = errno;
	errorText = SocketErrorCodes::getErrorDescription(errorCode, reqdOperation);
#endif
	
}


void NetworkComponent::clearError()
{
	errorCode = 0;
	errorText = NETWORK_COMPONENT_ERROR_NO_ERROR;
}
