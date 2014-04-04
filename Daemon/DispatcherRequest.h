#ifndef _TRANSPORT_REQUEST_
#define _TRANSPORT_REQUEST_

#include <string>

using namespace std;

/**
 * This class represents a dispatcher request. To simplify things, for each
 * client we create an object of this type (ie., this is the abstractization of a client)
 */
class DispatcherRequest
{
public:

    /**
     * Constructor. Creates a new object. Te string is the following format: NMS_INIT(protocol:port)
     */
    DispatcherRequest ( const string& s );

    /**
     * Returns the port of the request
     */
    int getPort() const
    {
        return port;
    }

    /**
     * Returns the protocol of the request.
     */
    const string& getProtocol() const
    {
        return protocol;
    }

    bool isValid() const
    {
        return valid;
    }

private:

    /**
     * Returns true if the protocol is supported or not
     */
    bool isValidProtocol ( const string& prot ) const;

private:

    // the protocol. Can be: tcp/udp. At this version only: tcp
    string protocol;

    // the requested port
    int port;

    // whether this Transport Request is valid or not
    bool valid;

};


#endif
