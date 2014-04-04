#ifndef _COMMAND_HELLO_H_
#define _COMMAND_HELLO_H_

#include "CommandInterface.h"
#include "ClientIdentity.h"

#include <stdio.h>
#include <string>
#include <sstream>
#include <unistd.h>

using namespace std;

/**
 * Implementation of the HELLO command
 */
class CommandHELLO : public CommandInterface
{
public:

    /**
     * Creates a new HELLO command that will go to the Dispatcher as the first brick of communication.
     */
    CommandHELLO ( ClientIdentity* cid, int port )
    {
        char curhost[256];
        gethostname ( curhost, 255 );
        HOSTENT* host = gethostbyname ( curhost );
        char hostIp[256];
        sprintf ( hostIp, "%i.%i.%i.%i", ( unsigned char ) host->h_addr_list[0][0],
                  ( unsigned char ) host->h_addr_list[0][1],
                  ( unsigned char ) host->h_addr_list[0][2],
                  ( unsigned char ) host->h_addr_list[0][3] );
        stringstream ss;
        ss << COMMAND_HELLO << COMMAND_SEPARATOR1 << cid->getIdentityDescriptor() << COMMAND_SEPARATOR3 << hostIp << COMMAND_SEPARATOR2 << port;
        result = ss.str();
    }
};

#endif
