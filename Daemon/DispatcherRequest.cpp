#include "DispatcherRequest.h"
#include "Logger.h"
#include "constants.h"

#include <stdlib.h>
#include <string.h>

/**
 * Creates a new TransportRequest object
 */
DispatcherRequest::DispatcherRequest(const string& s):protocol(""), port(0), valid(true)
{
	LOG("Creating new transport request");
	LOG(s);
volatile int i=0;
volatile int len = s.length();

	// first step: skip NMS_INIT(
	i += string(COMMAND_NMS_INIT).length();

	if(i >= len)	// not a valid request
	{
		LOG("Invalid request. No parameters");
		valid = false;
		return;
	}

string prot = "";
	i++;
	while(i < len && s[i] != COMMAND_SEPARATOR2)	// retrieving the protocol
	{
		prot += s[i];
		i++;
	}
	if( i >= len || !isValidProtocol(prot))	// not a valid request
	{
		LOG("Invalid request, invalid protocol:");
		LOG(prot);
		valid = false;
		return;
	}
	i++;	// skip ':'
	protocol = prot;
string s_port = "";
	while(i < len && s[i] != ')')
	{
		s_port += s[i];
		i++;
	}
	if(i >= len)
	{
		LOG("Invalid request. Command not finished as requried");
		valid = false;
		return;
	}
	port = atoi(s_port.c_str());
	if(port <= 0)
	{
		LOG("Invalid request, invalid port ");
		LOG(s_port);
		valid = false;
		return;
	}
}

/**
 * Checks if the request was valid
 */
bool DispatcherRequest::isValidProtocol(const std::string &prot) const
{
	return prot == "tcp";
}
