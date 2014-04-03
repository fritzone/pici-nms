#include "PnmsSecureClientImpl.h"
#include "Transporter.h"
#include "SecureClientInitializer.h"
#include "ObjImplMapper.h"
#include "TransporterImpl.h"
#include "Logger.h"

/**
 * Constructor
 */
PnmsSecureClientImpl::PnmsSecureClientImpl(const string &name) : PnmsGenericClientImpl(name, SECURE_CLIENT)
{
	sci = dynamic_cast<SecureClientInitializer*>(ObjImplMapper<Transporter, TransporterImpl>::getImpl(const_cast<Transporter*>(transporter))->getInitializer());
	ownsTransporter = false;
}

/**
 * Constructor
 */
PnmsSecureClientImpl::PnmsSecureClientImpl(const std::string &_name, const std::string &configFileLocation) : PnmsGenericClientImpl(), ownsTransporter(false)
{	
	name = _name;
	sci = new(std::nothrow) SecureClientInitializer(configFileLocation);	// deleted in the TransporterImpl destructor
	if(NULL == sci)
	{
		LOG_ERR("Not enough memory to create a new SecureClientInitializer");
		return;
	}

	if(!sci->initialized())
	{
		LOG_ERR("Could not initialize the secure client");
		return;
	}
	transporter = new (std::nothrow) Transporter(sci);
	if(NULL == transporter)
	{
		LOG_ERR("Not enough memory to create a new Transporter object");
		delete sci;
		return;
	}
	identity = transporter->getIdentity();
	ownsTransporter = true;
}

/**
 * Destructor
 */
PnmsSecureClientImpl::~PnmsSecureClientImpl()
{
	if(ownsTransporter)
	{
		delete transporter;
	}
}

bool PnmsSecureClientImpl::initialized() const
{
	return sci->initialized();
}
