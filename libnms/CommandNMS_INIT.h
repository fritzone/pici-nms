#ifndef _COMMAND_NMS_INIT_H_
#define _COMMAND_NMS_INIT_H_

#include "CommandInterface.h"
#include "constants.h"
#include <sstream>

using namespace std;

/**
 * Represents the NMS_INNIT command sent to the Daemon
 */
class CommandNMS_INIT : public CommandInterface
{

public:

	/**
	 * Creates a new NMS_INIT command
	 */
	CommandNMS_INIT(const string& _protocol, int _port)
	{
	stringstream ss;
		ss << COMMAND_NMS_INIT << "(" << _protocol << ":" << _port << ")";
		result = ss.str();
	}
};

#endif
