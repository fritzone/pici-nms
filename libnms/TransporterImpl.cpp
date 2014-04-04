#include "Logger.h"
#include "constants.h"
#include "Connection.h"
#include "NetworkAddress.h"
#include "TransporterImpl.h"
#include "Transporter.h"
#include "Receiver.h"
#include "Message.h"
#include "MessageImpl.h"
#include "Subscription.h"
#include "CommandNMS_INIT.h"
#include "CommandHELLO.h"
#include "CommandSUBSCRIBE.h"
#include "CommandUNSUBSCRIBE.h"
#include "CommandMESSAGE.h"
#include "PnmsUDPSocket.h"
#include "PnmsTCPSocket.h"
#include "TcpThread.h"
#include "LocalTCPClientFactory.h"
#include "DynamicClientInitializer.h"
#include "SecureClientInitializer.h"

#include "ThreadedTCPServer.h"
#include "TCPServerThread.h"
#include "ClientAcceptor.h"
#include "AbstractServerClientFactory.h"

#include <stdio.h>

#include <time.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

int DYNAMIC_CLIENT = 0;
int SECURE_CLIENT = 1;
int TRUSTED_CLIENT = 2;

using namespace std;

/**
 * Creates a new TransporterImpl object using the client type got as parameter
 */
TransporterImpl::TransporterImpl ( int method ) :  dispatcherAddress ( NULL ), freePort ( -1 ), tcpThread ( NULL ),
    localTcpServer ( NULL ), tcpcf ( NULL ), ca ( NULL ), initializer ( NULL ),
    identity ( NULL )
{
    if ( SECURE_CLIENT == method )
    {
        initializer = new ( std::nothrow ) SecureClientInitializer();
        if ( NULL == initializer )
        {
            LOG_ERR ( "Not enough memory to create a new DynamicClientInitializer" );
            return;
        }

        if ( !initializer->initialized() )
        {
            initializer->forceFail();
            return;
        }
    }
    else
    {
        initializer = new ( std::nothrow ) DynamicClientInitializer();
        if ( NULL == initializer )
        {
            LOG_ERR ( "Not enough memory to create a new DynamicClientInitializer" );
            return;
        }
        if ( DYNAMIC_CLIENT != method )
        {
            LOG_ERR ( "Created a dynamic client because of a wrong configuration issue" );
        }
    }

    if ( !initializer->initializeClient() )
    {
        initializer->forceFail();
        return;
    }

    if ( !localInit() )
    {
        initializer->forceFail();
    }
}

/**
 * Local initialization
 */
TransporterImpl::TransporterImpl ( AbstractClientInitializer* initer ) : initializer ( initer )
{
    if ( NULL == initializer )
    {
        LOG_ERR ( "Cannot initialize from a NULL initializer" );
        return ;
    }
    if ( !initializer->initializeClient() )
    {
        initializer->forceFail();
        return;
    }

    if ( !localInit() )
    {
        initializer->forceFail();
    }
}

/**
 * Destroys an existing TransporterImpl object
 */
TransporterImpl::~TransporterImpl ( void )
{
    // execute the Unsubscribe code!!!!
    while ( subscriptions.size() > 0 )
    {
        vector<Subscription*>::iterator iter = subscriptions.begin();
        unsubscribe ( ( *iter )->subject );
    }

    if ( localTcpServer != NULL )
    {
        localTcpServer->stop();
    }

    if ( NULL != initializer )
    {
        delete initializer;
    }
    if ( NULL != dispatcherAddress )
    {
        delete dispatcherAddress;
    }
    if ( NULL != identity )
    {
        delete identity;
    }
    if ( NULL != localTcpServer )
    {
        delete localTcpServer;
    }
    if ( NULL != tcpcf )
    {
        delete tcpcf;
    }
    if ( NULL != ca )
    {
        delete ca;
    }
}

/**
 * Initialization of the most important transporter impl stuff
 */
bool TransporterImpl::localInit()
{

    if ( NULL == initializer )
    {
        LOG_ERR ( "While initializing the initializer is NULL" );
        return false;
    }
    // get the dispatcher address
    dispatcherAddress = initializer->getDispatcherAddress();
    if ( !dispatcherAddress )
    {
        LOG_ERR ( "Dispatcher address mismatch" );
        return false;
    }

    // retrieve the client identity
    identity = initializer->retrieveClientIdentity();
    if ( !identity )
    {
        LOG_ERR ( "Client Identity could not be established" );
        return false;
    }

    // create a new thread for the local TCP server
    tcpThread = new ( std::nothrow ) TcpThread ( this );
    if ( !tcpThread )
    {
        LOG_ERR ( "TCP Server's Thread could not be created" );
        return false;
    }

    // create the server itself
    localTcpServer = new ( std::nothrow ) ThreadedTCPServer ( tcpThread );
    if ( !localTcpServer )
    {
        LOG_ERR ( "Cannot create local TCP server" );
        return false;
    }

    // create the local client factory for the server
    tcpcf = new ( std::nothrow ) LocalTCPClientFactory ( this );
    if ( !tcpcf )
    {
        LOG_ERR ( "Cannot create client factory" );
        return false;
    }

    // create the client acceptor from the client factor
    ca = new ( std::nothrow ) ClientAcceptor ( tcpcf );
    if ( !ca )
    {
        LOG_ERR ( "Cannot create ClientAcceptor" );
        return false;
    }

    // set the acceptor of the server
    localTcpServer->setAcceptor ( ca );

    // find the first free port where we can bind the local TCP server
    freePort = STARTING_TCP_PORT - 1;
    bool found = false;
    NetworkAddress localAddr ( htonl ( INADDR_ANY ), freePort );
    while ( !found && freePort < LAST_CHECKED_TCP_PORT )
    {
        freePort ++;
        localAddr.setPort ( freePort );
        if ( localTcpServer->bind ( &localAddr ) )
        {
            found = true;
        }
    }
    if ( freePort == LAST_CHECKED_TCP_PORT )
    {
        LOG_ERR ( "No free port found in the range 45000 - 65000" );
        return false;
    }

    // send a "HELLO" to the dispatcher to notify it with the settings
    if ( !sendHelloToDispatcher() )
    {
        LOG_ERR ( "Cannot send a hello to the dispatcher" );
        return false;
    }

    // the local TCP server starts listening
    if ( !localTcpServer->listen() )
    {
        LOG_ERR ( "Listen fails on local TCP Server" );
        return false;
    }

    // and its thread is started
    if ( !localTcpServer->start() )
    {
        LOG_ERR ( "Could not start local TCP server" );
        return false;
    }

    return true;
}

/**
 * Transfers the control to the given Receiver class.
 */
void TransporterImpl::handleMessage ( const string& subject, const Message& msg )
{
    vector<Subscription*>::iterator iter;
    for ( iter = subscriptions.begin(); iter < subscriptions.end(); iter++ )
    {
        if ( ( ( Subscription* ) ( *iter ) )->receives ( subject ) )
        {
            ( *iter )->theReceiver->receive ( msg );
            // here the response can be: TransporterImpl::messageLater, NULL
            // or a valid Message object.
            // The dispatcher handles the responses to asynchronous messages.
            return ;
        }
    }
    // here no subscriptions were found. Just ignore it.
}

/**
 * Returns if this object is initialized or not
 */
bool TransporterImpl::isInitialized()
{
    if ( NULL == initializer )
    {
        return false;
    }
    return initializer->initialized();
}

ClientIdentity* TransporterImpl::getClientIdentity()
{
    return initializer->retrieveClientIdentity();
}

/**
 * Executes the specified subscription
 */
bool TransporterImpl::subscribe ( const string& subject, Receiver* theReceiver )
{
    // firstly: send the subscribe message
    PnmsTCPSocket socketToDispatcher ( dispatcherAddress );
    CommandSUBSCRIBE cmdSubs ( identity, subject );
    string ack = socketToDispatcher.send ( &cmdSubs );
    // then add a new subscription
    Subscription* sub = new ( std::nothrow ) Subscription ( subject, theReceiver );
    if ( NULL == sub )
    {
        LOG_ERR ( "Not enough memory to create a new Subscription object" );
        return false;
    }
    subscriptions.push_back ( sub );
    return true;
}

/**
 * Unsubscribes from the given subject. It's the client applications role
 * to delete the receiver object.
 */
bool TransporterImpl::unsubscribe ( const string& theSubject )
{
    // firstly: send the unsubscribe message
    PnmsTCPSocket socketToDispatcher ( dispatcherAddress );
    CommandUNSUBSCRIBE cmdUnsub ( identity, theSubject );
    string ack = socketToDispatcher.send ( &cmdUnsub );

    //cout << "Unsibscribed from " << theSubject << endl;
    // then remove the subscription
    size_t i = 0;
    while ( i < subscriptions.size() )
    {
        if ( subscriptions[i]->subject == theSubject )
        {
            delete * ( subscriptions.begin() + i );
            subscriptions.erase ( subscriptions.begin() + i );
        }
        i++;
    }
    return true;
}

/**
 * Send the given message to the given subject list
 */
bool TransporterImpl::sendMessage ( const string& subject, const Message& msg )
{
    // firstly: send the unsubscribe message
    PnmsTCPSocket socketToDispatcher ( dispatcherAddress );
    CommandMESSAGE cmdMsg ( identity, subject, &msg, false );
    string msgAck = socketToDispatcher.send ( &cmdMsg );
    return msgAck.length() > 0;
}

/**
 * This method sends the given message to the specified Message, and waits for the
 * response of this message, which is returned. If no response is sent in the
 * given time interval, returns NULL.
 */
Message* TransporterImpl::sendAndWaitAnswer ( string subject, Message* msg, int timeout )
{
    PnmsTCPSocket socketToDispatcher ( dispatcherAddress );
    CommandMESSAGE cmdMsg ( identity, subject, msg, true );
    string reply = socketToDispatcher.send ( &cmdMsg, timeout );
//  cout << reply;
    // checking whether the return text contains "ERROR" or not...
    // when yes, it means, the dispatcher could not communicate with
    // the other end of the communication pipeline
    if ( reply == STR_ERROR )
    {
        //return new(std::nothrow) ErrorMessage(ERR_COMMUNICATION);
    }
    // checking whether  the synchResp is STR_NO_RESPONSE.
    // if yes, simply return an empty message.
    if ( reply == STR_NO_RESPONSE )
    {
        return new ( std::nothrow ) Message();
    }
    // here the synchResp sholud contain a serialized message
    Message* resp = MessageImpl::deserialize ( reply.c_str() );
    return resp;
}

/**
 * Sends the HELLO command to the dispatcher
 */
bool TransporterImpl::sendHelloToDispatcher()
{
    PnmsTCPSocket socketToDispatcher ( dispatcherAddress );
    CommandHELLO cmdHello ( identity, freePort );
    string ack = socketToDispatcher.send ( &cmdHello );
    // ack should contain the acknowledgment, and validate it !!!
    return true;
}

/**
 * Checks if this transporter is subscribed to this subject or not
 */
bool TransporterImpl::isSubscribed ( const string& subj )
{
    size_t i = 0;
    while ( i < subscriptions.size() )
    {
        if ( subscriptions[i]->subject == subj )
        {
            return true;
        }
        i++;
    }
    return false;
}