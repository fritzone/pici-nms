#ifndef _COMMAND_MESSAGE_H_
#define _COMMAND_MESSAGE_H_

#include "CommandInterface.h"
#include "Message.h"
#include "ClientIdentity.h"
#include "ObjImplMapper.h"

#include <sstream>

using namespace std;

/**
* Class abstractizing the MESSAGE message
*/
class CommandMESSAGE : public CommandInterface
{
public:

	/**
	* Constructor
	*/
	CommandMESSAGE(ClientIdentity* cid, const string& subject, const Message* msg, bool synch)
	{
		stringstream ss;
		ss << COMMAND_MESSAGE << COMMAND_SEPARATOR1 << cid->getIdentityDescriptor() << COMMAND_SEPARATOR2 << subject << COMMAND_SEPARATOR2
			<< (synch?STR_SYNCH:STR_ASYNCH) << COMMAND_SEPARATOR2 << 
			ObjImplMapper<Message, MessageImpl>::getImpl(const_cast<Message*>(msg))->getTtl() << COMMAND_SEPARATOR2 << ObjImplMapper<Message, MessageImpl>::getImpl(const_cast<Message*>(msg))->serialize();
		result = ss.str();
	}
};

#endif
