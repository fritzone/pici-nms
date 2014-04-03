#ifndef _COMMAND_INTERFACE_H_
#define _COMMAND_INTERFACE_H_

#include <string>

using namespace std;

/**
 * Abstract class for all the commands that will be implemented in the system
 */
class CommandInterface
{
public:
	
	/**
	 * Returns the command as a string object so that it can be sent over the wire.
	 * DO NOT RETURN A LOCAL OBJECT FROM THIS METHOD
	 */
	const string asString() const
	{
		return result;
	}

protected:
	string result;
};

#endif
