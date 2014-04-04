#include "ConnectionThread.h"

#include "AbstractInitializer.h"
#include "Connection.h"
#include "ClientIdentity.h"
#include "Message.h"
#include "MessageImpl.h"
#include "TransporterImpl.h"
#include "ObjImplMapper.h"

#include "constants.h"
#include "Logger.h"
#include "AbstractSocket.h"
#include "Mutex.h"
#include "CommandUtils.h"
#include "PnmsTCPSocket.h"

#include <string.h>
#include <stdlib.h>

#include <sstream>
#include <string>

using namespace std;

Mutex ConnectionThread::connectionThreadMutex;

/**
 * Constructor
 */
ConnectionThread::ConnectionThread ( Connection* _conn ) : Thread(), connection ( _conn )
{
}

/**
 * Processing a message from the dispatcher (or another client). Right now the message looks like:
 * MESSAGE#18:HELLO.B:ASYNCH:86400000:<Message> ... </Message>
 */
void* ConnectionThread::process()
{
    int lockMutex = connectionThreadMutex.lock();
    if ( lockMutex != 0 )
    {
        LOG ( "Cannot lock mutex, client rejected" );
        delete connection;
        return NULL;
    }

    TransporterImpl* transp = connection->getTransporter(); // the connection's transporter object
    AbstractSocket* socketFromDispatcher = connection->getSocket(); // the connections socket
    string msgFromDisp = socketFromDispatcher->receive();   // FS_SERV1

    if ( msgFromDisp.length() == 0 )
    {
        LOG ( "Error while receiving main data stream" );
        socketFromDispatcher->close();
        connectionThreadMutex.unlock();
        delete connection;
        return NULL;
    }
    // the command. It should be either 'PING' or 'MESSAGE'
    string cmd = CommandUtils::consume ( msgFromDisp, '#' );

    if ( cmd == PING ) // checking whether we must respond to a PING
    {
        if ( !socketFromDispatcher->send ( PONG ) )
        {
            LOG ( "Error sending Pong" );
            socketFromDispatcher->close();
        }
        delete connection;
        connectionThreadMutex.unlock();
        return NULL;
    }

    // Firstly finding the client number and validating it to our client number
    string clientNo = CommandUtils::consume ( msgFromDisp, ':' );
    if ( clientNo != transp->getClientIdentity()->getIdentityDescriptor() )
    {
        LOG_ERR ( "This message was not intended to this client" );
        socketFromDispatcher->close();
        delete connection;
        connectionThreadMutex.unlock();
        return NULL;
    }

    // then fetching the subject and checking if we are actually subscribed to this subject
    string subj = CommandUtils::consume ( msgFromDisp, ':' );
    if ( !transp->isSubscribed ( subj ) )
    {
        LOG_ERR ( "This client is not subscribed to this subject" );
        socketFromDispatcher->close();
        delete connection;
        connectionThreadMutex.unlock();
        return NULL;
    }

    // then fetching the message type, and verifying if it's valid or not
    string msgType = CommandUtils::consume ( msgFromDisp, ':' ); // SYNCH or ASYNCH, but right now only ASYNCH
    if ( msgType != STR_ASYNCH )
    {
        LOG_ERR ( "This client does not support this message type" );
        socketFromDispatcher->close();
        delete connection;
        connectionThreadMutex.unlock();
        return NULL;
    }

    // and finally fetching the TTL part of the message and ignoring it for now
    string sTTL = CommandUtils::consume ( msgFromDisp, ':' );   // the TTL of the message

    // now in msgFromDisp there is the pure XML only
    Message* msg = MessageImpl::deserialize ( msgFromDisp.c_str() );

    LOG ( "Handling the message" );
    transp->handleMessage ( subj, *msg );
    delete msg;

    // and finally sending back that the message was handled as normally
    TCPSocket* pnmss = dynamic_cast<TCPSocket*> ( socketFromDispatcher );
    if ( pnmss )
    {
        if ( !pnmss->send ( "-3" ) )                // FS_SERV2
        {
            LOG ( "Cannot send size acknowledgment to outside" );
            socketFromDispatcher->close();
            delete connection;
            connectionThreadMutex.unlock();
            return NULL;
        }
    }

    delete connection;
    connectionThreadMutex.unlock();

    LOG ( "Leaving" );
    return NULL;
}
