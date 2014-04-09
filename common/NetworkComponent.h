#ifndef _NETWORK_COMPONENT_H_
#define _NETWORK_COMPONENT_H_

#include <string>

using namespace std;

/**
 * Some basic class for components based on network object, purely for error handling.
 */
class NetworkComponent
{
    friend class UDPSocket;
    friend class TCPSocket;
    friend class TCPServer;

public:

    /**
     * Trivial constructor, initializes everything to the default values
     */
    NetworkComponent();

    virtual ~NetworkComponent() {}

    /**
     * Returns the error text of this component
     */
    const string& getError() const
    {
        return errorText;
    }

    /**
     * Returns the state of the initialization of this network component
     */
    bool isInitialized() const
    {
        return initialized;
    }

    /**
     * Returns the error code of this network component.
     */
    int getErrorCode() const
    {
        return errorCode;
    }

protected:

    /**
     * Populate the error code based on the last error
     */
    void populateErrorCode (
#ifndef _WIN32
        int reqdOperation
#endif
    );

    /**
     * Clears any errors we might have
     */
    void clearError();


private:

    // whether this socket was successfully initialized or not
    bool initialized;

    // the last error text of this socket
    string errorText;

    // the error code
    int errorCode;


};

#endif
