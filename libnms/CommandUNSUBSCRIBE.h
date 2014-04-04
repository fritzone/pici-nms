#ifndef _COMMAND_UNSUBSCRIBE_H_
#define _COMMAND_UNSUBSCRIBE_H_

#include "CommandInterface.h"
#include "ClientIdentity.h"

#include <sstream>

using namespace std;

/**
 * Class abstractizing the SUBSCRIBE message
 */
class CommandUNSUBSCRIBE : public CommandInterface
{
public:

    /**
     * Constructor
     */
    CommandUNSUBSCRIBE ( ClientIdentity* cid, const string& subject )
    {
        stringstream ss;
        ss << COMMAND_UNSUBSCRIBE << COMMAND_SEPARATOR1 << cid->getIdentityDescriptor() << COMMAND_SEPARATOR2 << subject;
        result = ss.str();
    }
};

#endif
