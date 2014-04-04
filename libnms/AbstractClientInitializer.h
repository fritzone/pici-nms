#ifndef _ABSTRACT_CLIENT_INITIALIZER_H_
#define _ABSTRACT_CLIENT_INITIALIZER_H_

#include "AbstractInitializer.h"
#include "constants.h"

class ClientIdentity;
class NetworkAddress;

/**
 * Abstract initializer for clients
 */
class AbstractClientInitializer : public AbstractInitializer
{

public:

    /**
     * Constructor
     */
    AbstractClientInitializer();

    /**
     * Initializes the client
     */
    virtual bool initializeClient() = 0;

    /**
     * Retrieves the client's identity after a successful initialization
     */
    ClientIdentity* retrieveClientIdentity();

    /**
     * Returns the dispatcher address to the caller
     */
    NetworkAddress* getDispatcherAddress();

protected:

    /**
     * Basic initialization steps.
     */
    bool basicInit();

    /**
     * Analyzes the data received from the daemon, either on UDP, either on TCP.
     * Initializes the identity of the client
     */
    bool analyzeResponse ( const char* response );

#ifdef _WIN32

    /**
     * initializes the Winsock interface
     */
    bool initWinsock();

#endif

private:

    // we need it for the destructor
    int startupErrorCode;

    // the address where the dispatcher is
    NetworkAddress* dispatcherAddress;

    // the identity of the client
    ClientIdentity* cid;

};

#endif
