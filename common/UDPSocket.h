#pragma  once
#ifndef _UDP_SOCKET_H_
#define _UDP_SOCKET_H_

#ifdef _WIN32
#include <WinSock2.h>       // must be included before windows.h or it will mess up the code :(
#endif

#include "AbstractSocket.h"

/**
 * Class representing a UDP socket, the one that's used to send the init message to the Daemon
 * in case of an unencrypted client
 */
class UDPSocket : public AbstractSocket
{
public:

    /**
     * Constructor
     */
    UDPSocket();

    /**
     * Sets this socket in a broadcasting mode. This only works for UDP sockets
     * @return the status of the operation (true - success, false failure)
     */
    bool enableBroadcast();

    /**
     * Connects the socket to the given address. For UDP sockets this is merely setting the
     * naddress member of the class.
     * @param address - the network address where this socket is connected
     */
    virtual bool connectTo ( const NetworkAddress* addrs );

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
    virtual bool send ( const std::string& data );


protected:

    /**
     * Creates the actual UDP Socket.
     * @return the status of the operation (true - success, false failure)
     */
    bool createSocket();
};

#endif
