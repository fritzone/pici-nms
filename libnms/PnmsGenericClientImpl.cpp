#include "PnmsGenericClientImpl.h"
#include "Transporter.h"
#include "Logger.h"

/**
 * Constructor
 */
PnmsGenericClientImpl::PnmsGenericClientImpl ( const string& _name, int clientType ) : name(_name)
{
    transporter = new ( std::nothrow ) Transporter ( clientType );
    if ( NULL == transporter )
    {
        LOG_ERR ( "Not enough memory to create a new Transporter" );
        identity = NULL;
        return;
    }
    identity = transporter->getIdentity();
}

/**
 * Default constructor
 */
PnmsGenericClientImpl::PnmsGenericClientImpl() : identity ( NULL ), transporter ( NULL ), name ( "" )
{

}

PnmsGenericClientImpl::~PnmsGenericClientImpl()
{
    if ( transporter != NULL )
    {
        delete transporter;
    }
}

Transporter* PnmsGenericClientImpl::getTransporter() const
{
    return transporter;
}

const ClientIdentity* PnmsGenericClientImpl::getIdentity() const
{
    return identity;
}

bool PnmsGenericClientImpl::isInitialized() const
{
    return transporter->isInitialized();
}

bool PnmsGenericClientImpl::subscribe ( const std::string& subject, Receiver* receiver )
{
    return transporter->subscribe ( subject, receiver );
}

bool PnmsGenericClientImpl::publishMessage ( const std::string& subject, const Message& msg )
{
    return transporter->sendMessage ( subject, msg );
}

bool PnmsGenericClientImpl::unsubscribe ( const std::string& subject )
{
    return transporter->unsubscribe ( subject );
}
