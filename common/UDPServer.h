#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

#include "BasicServerImpl.h"

class UDPSocket;

/**
 * Class representing a UDP Server
 */
class UDPServer : public BasicServerImpl
{

public:

    /**
     * Constructor
     */
    UDPServer();

    /**
     * Constructor
     */
    UDPServer ( ClientAcceptor* acc );

    /**
     * Returns the socket object of the server
     * @return the socket
     */
    UDPSocket* getSocket() const;
};

#endif
