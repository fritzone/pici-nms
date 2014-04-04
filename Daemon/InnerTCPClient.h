#ifndef _INNER_TCP_CLIENT_H_
#define _INNER_TCP_CLIENT_H_

#include "AbstractServerClient.h"
#include "AbstractSocket.h"
#include "NetworkAddress.h"

class Daemon;

/**
 * This is a client that connects to the daemon from the inner network
 */
class InnerTCPClient : public AbstractServerClient
{
public:

    /**
     * Constructor
     */
    InnerTCPClient ( Daemon* dmn );

    /**
     * Called when a client connected to the daemon from the inner network
     */
    bool onConnect ( AbstractSocket* sock, NetworkAddress* addr );

private:

    // the daemon object of this client
    Daemon* daemon;
};

#endif
