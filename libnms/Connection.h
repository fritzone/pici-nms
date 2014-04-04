#ifndef _CONNECTION_H_
#define _CONNECTION_H_

class TransporterImpl;
class TCPSocket;
class AbstractSocket;

/**
 * This class collects the data from a connection, that receives from the Disptacher
 * The socket is the socket, that arrived from the Dispatcher
 * The transporter is the transporter object which handles this conenctions data
 */
class Connection
{
public:

    /**
     * Constructor. Creates a new object with the given socket and transporter implementation
     */
    Connection ( AbstractSocket* sck, TransporterImpl* transp );

    /**
     * Destructor
     */
    ~Connection();

    /**
     * Returns the transported
     */
    TransporterImpl* getTransporter();

    /**
     * Returns the socket
     */
    AbstractSocket* getSocket();

private:

    // the transporter object
    TransporterImpl* transporter;

    // the socket which came from the disptacher
    TCPSocket* sock;
};


#endif
