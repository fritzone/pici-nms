#ifndef _ABSTRACT_SOCKET_H_
#define _ABSTRACT_SOCKET_H_

#ifdef _WIN32
#ifndef CYGWIN
#include <WinSock2.h>
#endif
#else
#include "Win2Lin.h"
#endif

#include "NetworkComponent.h"

class NetworkAddress;

/**
 * Basic class for sockets. The UDP and TCP sockets are derivates of this
 * class, providing specific construction methods whilst the basic operations
 * are the same for each socket. This class inherits from the NetworkComponent
 * so that the generic network error messages are usable by this class too.
 */
class AbstractSocket : public NetworkComponent
{

    friend class BasicServerImpl;
    friend class TCPServer;

public:

    /**
     * Closes the socket
     * @return true if the close operation was succesfull or false if not
     */
    bool close();

    /**
     * Connects the socket to the given address.
     * @param address - the network address where this socket is connected
     */
    virtual bool connectTo ( const NetworkAddress* addrs ) = 0;

    /**
     * Enables the non-blocking feature of the socket
     * @return true if the operation succeeded or false if not
     */
    bool setNonBlocking();


    /**
     * Disables the non-blocking feature of the socket
     * @return true if the operation succeeded or false if not
     */
    bool setBlocking();

    /**
     * Receives a string on this socket. Optionally returns the address from where we've read
     * @param from - the address from which we've received the string
     * @return the received string
     */
    virtual string receive ( NetworkAddress* from = NULL ) = 0;

    /**
     * Sends the given string through the socket
     * @param data - the string to be sent
     * @return true if the data was sent successfully, false if not
     */
    virtual bool send ( const string& data ) = 0;

    /**
     * Returns the OS level socket object of this Abstract Socket
     * @return the OS level socket
     */
    SOCKET getOSSocket() const
    {
        return theSocket;
    }

protected:

    /**
     * Constructor. Is not supposed to do anything and is not supposed to be visible outside this class
     * and its descendants
     */
    AbstractSocket() : NetworkComponent(), theSocket ( INVALID_SOCKET ), naddress ( NULL ), closed ( false )
    {
    }

    /**
     * Constructor. Used to initialize the socket to a specific value, usually called after a succesful
     * "accept" call in a server class.
     * @param sock - the socket as provided by the client of this class
     */
    AbstractSocket ( SOCKET sock ) : NetworkComponent(), theSocket ( sock ), naddress ( NULL ), closed ( false )
    {
    }

    /**
     * Destructor. Closes the socket.
     */
    virtual ~AbstractSocket()
    {
        if ( !closed )
        {
            close();
        }
    }

protected:

    // this is the socket
    SOCKET theSocket;

    // where this socket is connected right now ...
    NetworkAddress* naddress;

private:

    // true if this socket is closed, false if it's open.
    bool closed;
};

#endif
