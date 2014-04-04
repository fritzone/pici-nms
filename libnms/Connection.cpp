#include "Connection.h"
#include "TcpSocket.h"

/**
 * Creates a new connection object
 */
Connection::Connection ( AbstractSocket* sck, TransporterImpl* transp ) :
    transporter ( transp ), sock ( dynamic_cast<TCPSocket*> ( sck ) )
{
}

Connection::~Connection()
{
    delete sock;    // this was created in the TCPServerThread::process
}

TransporterImpl* Connection::getTransporter()
{
    return transporter;
}

AbstractSocket* Connection::getSocket()
{
    return sock;
}

