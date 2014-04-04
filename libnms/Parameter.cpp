#include "Parameter.h"
#include "xml_handler.h"
#include "ObjectFactory.h"
#include "ObjImplMapper.h"
#include "StringWrapper.h"
#include "ParameterImpl.h"
#include "IntWrapper.h"
#include "LongWrapper.h"
#include "CharWrapper.h"
#include "DoubleWrapper.h"
#include "BoolWrapper.h"
#include "FloatWrapper.h"
#include "BoolWrapper.h"
#include "StringWrapper.h"
#include "Logger.h"
#include "ParameterImpl.h"
#include "LongImpl.h"
#include "FloatImpl.h"
#include "BoolImpl.h"
#include "StringImpl.h"
#include "DoubleImpl.h"
#include "CharImpl.h"
#include "IntImpl.h"

/**
 * Constructor with the given name
 */
Parameter::Parameter ( const string& _name )
{
    ParameterImpl* pimpl = new ( std::nothrow ) ParameterImpl ( _name );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "Not enough memory to create a new ParameterImpl" );
        return;
    }
    ObjImplMapper<Parameter, ParameterImpl>::mapObjToImpl ( this, pimpl );
}

/**
 * Constructor with the given name and value
 */
Parameter::Parameter ( const std::string& _name, SerializableObject* _value )
{
    ParameterImpl* pimpl = new ( std::nothrow ) ParameterImpl ( _name, _value );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "Not enough memory to create a new ParameterImpl" );
        return;
    }
    ObjImplMapper<Parameter, ParameterImpl>::mapObjToImpl ( this, pimpl );
}

/**
 * Destructor
 */
Parameter::~Parameter()
{
    delete ObjImplMapper<Parameter, ParameterImpl>::getImpl ( this );
    ObjImplMapper<Parameter, ParameterImpl>::removeImpl ( this );
}

/**
 * Returns the type of the data as a string that can be put into the XML without too much complication
 * @return the type of this class as a text
 */
const string& Parameter::type() const
{
    return ParameterImpl::TYPESTR_PARAMETER;
}

/**
 * Returns the name of this parameter
 */
const string& Parameter::name() const
{
    return ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) )->name;
}

/**
 * Makes this parameter to be an int value
 */
Parameter& Parameter::operator = ( int value )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        return *this;
    }
    Integer* newInt = new ( std::nothrow ) Integer ( value );
    if ( NULL == newInt )
    {
        LOG_ERR ( "Not enough memory to create a new Integer" );
        return *this;
    }
    SerializableObject* so = pimpl->getValue();
    if ( NULL != so )
    {
        delete so;
    }
    pimpl->setValue ( newInt );
    return *this;
}


/**
 * Makes this parameter to be a float value
 */
Parameter& Parameter::operator = ( float value )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        return *this;
    }
    Float* newFloat = new ( std::nothrow ) Float ( value );
    if ( NULL == newFloat )
    {
        LOG_ERR ( "Not enough memory to create a new Float" );
        return *this;
    }
    SerializableObject* so = pimpl->getValue();
    if ( NULL != so )
    {
        delete so;
    }
    pimpl->setValue ( newFloat );
    return *this;
}

/**
 * Makes this parameter to be a string value
 */
Parameter& Parameter::operator = ( const char* value )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        return *this;
    }
    String* newStr = new ( std::nothrow ) String ( value );
    if ( NULL == newStr )
    {
        LOG_ERR ( "Not enough memory to create a new String" );
        return *this;
    }
    SerializableObject* so = pimpl->getValue();
    if ( NULL != so )
    {
        delete so;
    }
    pimpl->setValue ( newStr );
    return *this;
}

/**
 * Makes this parameter to be a string value
 */
Parameter& Parameter::operator = ( bool value )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        return *this;
    }
    Bool* newBool = new ( std::nothrow ) Bool ( value );
    if ( NULL == newBool )
    {
        LOG_ERR ( "Not enough memory to create a new Bool" );
        return *this;
    }
    SerializableObject* so = pimpl->getValue();
    if ( NULL != so )
    {
        delete so;
    }
    pimpl->setValue ( newBool );
    return *this;
}

/**
 * Makes this parameter to be a char value
 */
Parameter& Parameter::operator = ( double value )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        return *this;
    }
    Double* newDouble = new ( std::nothrow ) Double ( value );
    if ( NULL == newDouble )
    {
        LOG_ERR ( "Not enough memory to create a new Double" );
        return *this;
    }
    SerializableObject* so = pimpl->getValue();
    if ( NULL != so )
    {
        delete so;
    }
    pimpl->setValue ( newDouble );
    return *this;
}

/**
 * Makes this parameter to be a char value
 */
Parameter& Parameter::operator = ( char value )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        return *this;
    }
    Char* newChar = new ( std::nothrow ) Char ( value );
    if ( NULL == newChar )
    {
        LOG_ERR ( "Not enough memory to create a new Char" );
        return *this;
    }
    SerializableObject* so = pimpl->getValue();
    if ( NULL != so )
    {
        delete so;
    }
    pimpl->setValue ( newChar );
    return *this;
}

/**
 * Makes this parameter to be a long value
 */
Parameter& Parameter::operator = ( long value )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        return *this;
    }
    Long* newLong = new ( std::nothrow ) Long ( value );
    if ( NULL == newLong )
    {
        LOG_ERR ( "Not enough memory to create a new Long" );
        return *this;
    }

    SerializableObject* so = pimpl->getValue();
    if ( NULL != so )
    {
        delete so;
    }
    pimpl->setValue ( newLong );
    return *this;
}


/**
 * This parameter as an int
 */
Parameter::operator int() const throw ( invalid_type, parameter_not_found )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        throw parameter_not_found ( name() );
    }
    Integer* isInt = dynamic_cast<Integer*> ( pimpl->getValue() );
    if ( NULL == isInt )
    {
        throw invalid_type ( IntImpl::TYPESTR_INTEGER, pimpl->getValue()->type() );
    }
    return isInt->operator int();
}

/**
 * This parameter as a float
 */
Parameter::operator float() const throw ( invalid_type, parameter_not_found )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        throw parameter_not_found ( name() );
    }
    Float* isFloat = dynamic_cast<Float*> ( pimpl->getValue() );
    if ( NULL == isFloat )
    {
        throw invalid_type ( FloatImpl::TYPESTR_FLOAT, pimpl->getValue()->type() );
    }
    return isFloat->operator float();
}


/**
 * This parameter as a string
 */
Parameter::operator const char* () const throw ( invalid_type, parameter_not_found )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        throw parameter_not_found ( name() );
    }
    String* isStr = dynamic_cast<String*> ( pimpl->getValue() );
    if ( NULL == isStr )
    {
        throw invalid_type ( StringImpl::TYPESTR_STRING, pimpl->getValue()->type() );
    }
    return isStr->c_str();
}


/**
 * This parameter as a boolean
 */
Parameter::operator bool() const throw ( invalid_type, parameter_not_found )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        throw parameter_not_found ( name() );
    }
    Bool* isBool = dynamic_cast<Bool*> ( pimpl->getValue() );
    if ( NULL == isBool )
    {
        throw invalid_type ( BoolImpl::TYPESTR_BOOL, pimpl->getValue()->type() );
    }
    return isBool->operator bool();
}


/**
 * This parameter as a long
 */
Parameter::operator long() const throw ( invalid_type, parameter_not_found )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        throw parameter_not_found ( name() );
    }
    Long* isLong = dynamic_cast<Long*> ( pimpl->getValue() );
    if ( NULL == isLong )
    {
        throw invalid_type ( LongImpl::TYPESTR_LONG, pimpl->getValue()->type() );
    }
    return isLong->operator long();
}


/**
 * This parameter as a double
 */
Parameter::operator double() const throw ( invalid_type, parameter_not_found )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        throw parameter_not_found ( name() );
    }
    Double* isDouble = dynamic_cast<Double*> ( pimpl->getValue() );
    if ( NULL == isDouble )
    {
        throw invalid_type ( DoubleImpl::TYPESTR_DOUBLE, pimpl->getValue()->type() );
    }
    return isDouble->operator double();
}

/**
 * This parameter as a char
 */
Parameter::operator char() const throw ( invalid_type, parameter_not_found )
{
    ParameterImpl* pimpl = ObjImplMapper<Parameter, ParameterImpl>::getImpl ( const_cast<Parameter*> ( this ) );
    if ( NULL == pimpl )
    {
        LOG_ERR ( "An implementation of a parameter is NULL. No operation was performed" );
        throw parameter_not_found ( name() );
    }
    Char* isChar = dynamic_cast<Char*> ( pimpl->getValue() );
    if ( NULL == isChar )
    {
        throw invalid_type ( CharImpl::TYPESTR_CHAR, pimpl->getValue()->type() );
    }
    return isChar->operator char();
}
