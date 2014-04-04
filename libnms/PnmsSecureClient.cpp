#include "PnmsSecureClient.h"
#include "PnmsSecureClientImpl.h"
#include "Transporter.h"
#include "ObjImplMapper.h"
#include "Logger.h"
#include "PnmsNetwork.h"

/**
 * Constructor. Creates a new Secure client
 */
PnmsSecureClient::PnmsSecureClient ( const std::string& clientName )
{
    if ( !PnmsNetwork::initialized )
    {
        PnmsNetwork::initialize();
    }

    PnmsSecureClientImpl* psimpl = new ( std::nothrow ) PnmsSecureClientImpl ( clientName );
    if ( NULL == psimpl )
    {
        LOG_ERR ( "Not enough memory to create a new PnmsSecureClientImpl" );
    }
    ObjImplMapper<PnmsSecureClient, PnmsSecureClientImpl>::mapObjToImpl ( this, psimpl );
}

/**
 * Destructor
 */
PnmsSecureClient::~PnmsSecureClient()
{
    delete ObjImplMapper<PnmsSecureClient, PnmsSecureClientImpl>::getImpl ( const_cast<PnmsSecureClient*> ( this ) );
}

/**
 * Constructor.
 */
PnmsSecureClient::PnmsSecureClient ( const std::string& name, const std::string& configFileLocation )
{
    if ( !PnmsNetwork::initialized )
    {
        PnmsNetwork::initialize();
    }

    PnmsSecureClientImpl* psimpl = new ( std::nothrow ) PnmsSecureClientImpl ( name, configFileLocation );
    if ( NULL == psimpl )
    {
        LOG_ERR ( "Not enough memory to create a new PnmsSecureClientImpl" );
    }
    ObjImplMapper<PnmsSecureClient, PnmsSecureClientImpl>::mapObjToImpl ( this, psimpl );
}

/**
 * Returns the initialization state of the client
 */
bool PnmsSecureClient::isInitialized() const
{
    if ( ObjImplMapper<PnmsSecureClient, PnmsSecureClientImpl>::getImpl ( const_cast<PnmsSecureClient*> ( this ) )->initialized() )
    {
        return ObjImplMapper<PnmsSecureClient, PnmsSecureClientImpl>::getImpl ( const_cast<PnmsSecureClient*> ( this ) )->isInitialized();
    }
    else
    {
        return false;
    }
}

/**
 * Subscribe to the given subject
 */
bool PnmsSecureClient::subscribe ( const std::string& subject, Receiver* receiver )
{
    return ObjImplMapper<PnmsSecureClient, PnmsSecureClientImpl>::getImpl ( const_cast<PnmsSecureClient*> ( this ) )->subscribe ( subject, receiver );
}

/**
 * Publishes the message to the Pnms network
 */
bool PnmsSecureClient::publishMessage ( const std::string& subject, const Message& msg )
{
    return ObjImplMapper<PnmsSecureClient, PnmsSecureClientImpl>::getImpl ( const_cast<PnmsSecureClient*> ( this ) )->publishMessage ( subject, msg );
}

