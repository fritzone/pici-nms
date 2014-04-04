#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_

#include "AbstractSocket.h"
class NetworkAddress;

/**
 * Represents an abstractization layer on top of the TCP socktes
 */
class TCPSocket : public AbstractSocket
{
    friend class TCPServer;
public:

    /**
     * Constructor
     */
    TCPSocket();

    /**
     * Destructor
     */
    ~TCPSocket();

    /**
     * Constructor from a given socket
     */
    TCPSocket ( SOCKET sock );

    /**
     * Connects this socket to the given address. For TCP Sockets this calls the "connect"
     * function from the socket library.
     * @param address - the network address where this socket is connected
     */
    bool connectTo ( const NetworkAddress* addrs );

    /**
     * Receives a string on this socket. Optionally returns the address from where we've read
     * @param from - the address from which we've received the string
     * @return the received string
     */
    virtual string receive ( NetworkAddress* from = NULL );

    /**
     * Sends the given string through the socket
     * @param data - the string to be sent
     * @return true if the data was sent successfully, false if not
     */
    virtual bool send ( const string& data );

protected:

    /**
     * Creates the actual UDP Socket.
     * @return the status of the operation (true - success, false failure)
     */
    bool createSocket();

private:

    /**
     * Simple wrapper for the send method, this may call the ::send method
     */
    bool sendWrapper ( const char* toSend, int len );
};

#endif
