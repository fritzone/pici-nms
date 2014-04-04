#ifndef _ABSTRACT_SERVER_H_
#define _ABSTRACT_SERVER_H_

#include "NetworkComponent.h"

class ClientAcceptor;

/**
 * Generic server interface. All servers must derive from this class, since this is the
 * one holding the client acceptor
 */
class AbstractServer : public NetworkComponent
{
public:

    /**
     * Constructor. Initializes the acceptor member of the class to the required value
     * @param acc - the new acceptor.
     */
    AbstractServer ( ClientAcceptor* acc ) : NetworkComponent(), acceptor ( acc )
    {
    }

    /**
     * Sets the acceptor of this server.
     * @param acc - the new acceptor
     */
    void setAcceptor ( ClientAcceptor* acc )
    {
        acceptor = acc;
    }

    /**
     * Returns the acceptor of this server.
     * @return the acceptor
     */
    ClientAcceptor* getAcceptor() const
    {
        return acceptor;
    }

protected:

    // this is the client acceptor which gets attention when a new client has connected.
    ClientAcceptor* acceptor;
};

#endif
