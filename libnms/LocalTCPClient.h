#ifndef _LOCAL_TCP_CLIENT_H_
#define _LOCAL_TCP_CLIENT_H_

#include "AbstractServerClient.h"
#include "AbstractSocket.h"
#include "NetworkAddress.h"

class TransporterImpl;

/**
 * Client of the local TCP Server. This gets activated when a connection from the Dispatcher
 * is being initiated.
 */
class LocalTCPClient : public AbstractServerClient
{
public:
    /**
     * Constructor. Creates a new object
     */
    LocalTCPClient ( TransporterImpl* );

    /**
     * Called when the Local TCP Server has accepted a client from the Dispatcher (or someone else)
     */
    bool onConnect ( AbstractSocket* sock, NetworkAddress* addr );

private:

    // the transporter object
    TransporterImpl* transp;
};

#endif
