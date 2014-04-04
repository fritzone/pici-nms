#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include "BasicServerImpl.h"

class TCPSocket;
class NetworkAddress;
class ClientAcceptor;

/**
 * Class representing a TCP Server. The implemented way of working of the TCP Servers
 * is to create a thread, which is started by the "start" method, and this thread
 * is waiting for an incoming connection using the accept method. When the accept method
 * returned a socket, the server thread creates a new thread (connection thread)
 * and creates a TCPClient object which is passed to the new thread, which on its turn
 * calls the clientAcceptor member's onClienConnected method with the given client.
 * The server which is created is by default a blocking server.
 */
class TCPServer : public BasicServerImpl
{
public:

    /**
     * Constructor. Does nothing, but initializes the members to NULL.
     */
    TCPServer();

    /**
     * Constructor. Initializes the acceptor ofthe class.
     * @param acc - the acceptor.
     */
    TCPServer ( ClientAcceptor* acc );

    /**
     * Performs the listen operation on this TCP Server.
     * @param backlog - the maximum length of waiting queued sockets
     * @return true in case of success, false in case of failure
     */
    bool listen ( int backlog = 5 );

    /**
     * Returns the socket object of the server
     * @return the socket
     */
    TCPSocket* getSocket() const;

};

#endif
