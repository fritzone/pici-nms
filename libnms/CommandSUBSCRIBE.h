#ifndef _COMMAND_SUBSCRIBE_H_
#define _COMMAND_SUBSCRIBE_H_

#include "CommandInterface.h"
#include "ClientIdentity.h"

#include <sstream>

using namespace std;

/**
 * Class abstraction for the SUBSCRIBE message
 */
class CommandSUBSCRIBE : public CommandInterface
{
public:

    /**
     * Constructor
     */
    CommandSUBSCRIBE ( ClientIdentity* cid, const string& subject )
    {
        stringstream ss;
        ss << COMMAND_SUBSCRIBE << COMMAND_SEPARATOR1 << cid->getIdentityDescriptor() << COMMAND_SEPARATOR2 << subject;
        result = ss.str();
    }
};

#endif
