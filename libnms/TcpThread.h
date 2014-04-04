#ifndef _TCPTHREAD_H_
#define _TCPTHREAD_H_

#include "TCPServerThread.h"

class TransporterImpl;

/**
 * Class representing the TCP Server Thread
 */
class TcpThread : public TCPServerThread
{
public:

    /**
     * Constructor
     */
    TcpThread ( TransporterImpl* );

private:

    // the transporter implementation
    TransporterImpl* transp;
};

#endif
