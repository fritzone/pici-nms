#include "PnmsNetwork.h"

#include "ObjectFactory.h"
#include "IntImpl.h"
#include "ParameterImpl.h"
#include "LongImpl.h"
#include "FloatImpl.h"
#include "BoolImpl.h"
#include "StringImpl.h"
#include "DoubleImpl.h"
#include "Logger.h"
#include "CharImpl.h"

bool PnmsNetwork::initialized = false;

/**
 * Initializes the
 */
bool PnmsNetwork::initialize()
{
    Logger::init ( "client.log" );

    // mapping the serializer of the Integer type
    ObjectFactory::mapDeserializer ( IntImpl::TYPESTR_INTEGER, ( DESERIALIZER ) IntImpl::deserializeInteger );
    ObjectFactory::mapSerializer ( IntImpl::TYPESTR_INTEGER, ( SERIALIZER ) IntImpl::serializeInteger );

    // mapping the serializer of the Parameter class
    ObjectFactory::mapSerializer ( ParameterImpl::TYPESTR_PARAMETER, ( SERIALIZER ) ParameterImpl::serializeParameter );
    ObjectFactory::mapDeserializer ( ParameterImpl::TYPESTR_PARAMETER, ( DESERIALIZER ) ParameterImpl::deserializeParameter );

    // mapping the serializer of the Float type
    ObjectFactory::mapDeserializer ( FloatImpl::TYPESTR_FLOAT, ( DESERIALIZER ) FloatImpl::deserializeFloat );
    ObjectFactory::mapSerializer ( FloatImpl::TYPESTR_FLOAT, ( SERIALIZER ) FloatImpl::serializeFloat );

    // mapping the serializer of the Long type
    ObjectFactory::mapDeserializer ( LongImpl::TYPESTR_LONG, ( DESERIALIZER ) LongImpl::deserializeLong );
    ObjectFactory::mapSerializer ( LongImpl::TYPESTR_LONG, ( SERIALIZER ) LongImpl::serializeLong );

    // mapping the serializer of the Bool type
    ObjectFactory::mapDeserializer ( BoolImpl::TYPESTR_BOOL, ( DESERIALIZER ) BoolImpl::deserializeBool );
    ObjectFactory::mapSerializer ( BoolImpl::TYPESTR_BOOL, ( SERIALIZER ) BoolImpl::serializeBool );

    // mapping the serializer of the String type
    ObjectFactory::mapDeserializer ( StringImpl::TYPESTR_STRING, ( DESERIALIZER ) StringImpl::deserializeString );
    ObjectFactory::mapSerializer ( StringImpl::TYPESTR_STRING, ( SERIALIZER ) StringImpl::serializeString );

    // mapping the serializer of the Double type
    ObjectFactory::mapDeserializer ( DoubleImpl::TYPESTR_DOUBLE, ( DESERIALIZER ) DoubleImpl::deserializeDouble );
    ObjectFactory::mapSerializer ( DoubleImpl::TYPESTR_DOUBLE, ( SERIALIZER ) DoubleImpl::serializeDouble );

    // mapping the serializer of the Char type
    ObjectFactory::mapDeserializer ( CharImpl::TYPESTR_CHAR, ( DESERIALIZER ) CharImpl::deserializeChar );
    ObjectFactory::mapSerializer ( CharImpl::TYPESTR_CHAR, ( SERIALIZER ) CharImpl::serializeChar );

    PnmsNetwork::initialized = true;

    return true;
}
