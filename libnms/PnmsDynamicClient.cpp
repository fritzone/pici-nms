#include "PnmsDynamicClient.h"
#include "PnmsDynamicClientImpl.h"
#include "Transporter.h"
#include "ObjImplMapper.h"
#include "Logger.h"
#include "PnmsNetwork.h"

/**
 * Constructor. Creates a new Dynamic client
 */
PnmsDynamicClient::PnmsDynamicClient ( const std::string& clientName )
{
    if ( !PnmsNetwork::initialized )
    {
        PnmsNetwork::initialize();
    }

    PnmsDynamicClientImpl* pdimpl = new ( std::nothrow ) PnmsDynamicClientImpl ( clientName );
    if ( NULL == pdimpl )
    {
        LOG_ERR ( "Not enough memory to create a new PnmsDynamicClientImpl" );
        return;
    }
    ObjImplMapper<PnmsDynamicClient, PnmsDynamicClientImpl>::mapObjToImpl ( this, pdimpl );
}

/**
 * Destructor
 */
PnmsDynamicClient::~PnmsDynamicClient()
{
    PnmsDynamicClientImpl* pimpl = ObjImplMapper<PnmsDynamicClient, PnmsDynamicClientImpl>::getImpl ( const_cast<PnmsDynamicClient*> ( this ) );
    ObjImplMapper<PnmsDynamicClient, PnmsDynamicClientImpl>::removeImpl ( this );
    delete pimpl;
}

/**
 * Returns the initialization state of the client
 */
bool PnmsDynamicClient::isInitialized() const
{
    return ObjImplMapper<PnmsDynamicClient, PnmsDynamicClientImpl>::getImpl ( const_cast<PnmsDynamicClient*> ( this ) )->isInitialized();
}

/**
 * Subscribe to the given subject
 */
bool PnmsDynamicClient::subscribe ( const std::string& subject, Receiver* receiver )
{
    return ObjImplMapper<PnmsDynamicClient, PnmsDynamicClientImpl>::getImpl ( const_cast<PnmsDynamicClient*> ( this ) )->subscribe ( subject, receiver );
}

/**
 * Publishes the message to the Pnms network
 */
bool PnmsDynamicClient::publishMessage ( const std::string& subject, const Message& msg )
{
    return ObjImplMapper<PnmsDynamicClient, PnmsDynamicClientImpl>::getImpl ( const_cast<PnmsDynamicClient*> ( this ) )->publishMessage ( subject, msg );
}

