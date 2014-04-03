#include "Transporter.h"
#include "TransporterImpl.h"
#include "Receiver.h"
#include "Message.h"
#include "ObjImplMapper.h"
#include "Logger.h"

Transporter::Transporter(int authenticationMethod)
{
TransporterImpl* timpl = new (std::nothrow) TransporterImpl(authenticationMethod);
	if(NULL == timpl)
	{
		LOG_ERR("Not enough memory to create a new TransporterImpl object");
	}
	ObjImplMapper<Transporter, TransporterImpl>::mapObjToImpl(this, timpl);
}

Transporter::Transporter(AbstractClientInitializer* initializer)
{
TransporterImpl* timpl = new (std::nothrow) TransporterImpl(initializer);
	if(NULL == timpl)
	{
		LOG_ERR("Not enough memory to create a new TransporterImpl object");
	}
	ObjImplMapper<Transporter, TransporterImpl>::mapObjToImpl(this, timpl);
}

Transporter::~Transporter()
{
	delete ObjImplMapper<Transporter, TransporterImpl>::getImpl(const_cast<Transporter*>(this));
}

bool Transporter::sendMessage(const string& subject, const Message& msg)
{
	return ObjImplMapper<Transporter, TransporterImpl>::getImpl(const_cast<Transporter*>(this))->sendMessage(subject, msg);
}

Message* Transporter::sendAndWaitAnswer(const string& subject, Message *msg, int timeout)
{
	return ObjImplMapper<Transporter, TransporterImpl>::getImpl(const_cast<Transporter*>(this))->sendAndWaitAnswer(subject, msg, timeout);
}

bool Transporter::subscribe(const string& subject, Receiver *theReceiver)
{
	return ObjImplMapper<Transporter, TransporterImpl>::getImpl(const_cast<Transporter*>(this))->subscribe(subject, theReceiver);
}

bool Transporter::isInitialized()
{
	return ObjImplMapper<Transporter, TransporterImpl>::getImpl(const_cast<Transporter*>(this))->isInitialized();
}
					
const ClientIdentity* Transporter::getIdentity()
{
	return ObjImplMapper<Transporter, TransporterImpl>::getImpl(const_cast<Transporter*>(this))->getClientIdentity();
}

bool Transporter::unsubscribe(const string& subject)
{
	return ObjImplMapper<Transporter, TransporterImpl>::getImpl(const_cast<Transporter*>(this))->unsubscribe(subject);
}
