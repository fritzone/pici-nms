#include "Message.h"

#include "Logger.h"

#include "Parameter.h"
#include "MessageImpl.h"
#include "StringWrapper.h"
#include "LongWrapper.h"
#include "BoolWrapper.h"
#include "DoubleWrapper.h"
#include "FloatWrapper.h"
#include "IntWrapper.h"
#include "ObjImplMapper.h"

using namespace std;

/**
 * Constructor
 */
Message::Message()
{
    MessageImpl* mimpl = new ( std::nothrow ) MessageImpl ( TTL_24H );
    if ( NULL == mimpl )
    {
        LOG_ERR ( "Not enough memory to create a new message implementation" );
        return;
    }
    ObjImplMapper<Message, MessageImpl>::mapObjToImpl ( this, mimpl );
}

Message::Message ( int ttl )
{
    MessageImpl* mimpl = new ( std::nothrow ) MessageImpl ( ttl );
    if ( NULL == mimpl )
    {
        LOG_ERR ( "Not enough memory to create a new message implementation" );
        return;
    }
    ObjImplMapper<Message, MessageImpl>::mapObjToImpl ( this, mimpl );
}

/**
 * Destructor
 */
Message::~Message()
{
    delete ObjImplMapper<Message, MessageImpl>::getImpl ( this );
    ObjImplMapper<Message, MessageImpl>::removeImpl ( this );
}

/**
 * Adds an integer to the message
 */
bool Message::add ( const string& name, int value )
{
    Integer* newInt = new ( std::nothrow ) Integer ( value );
    if ( NULL == newInt )
    {
        LOG_ERR ( "Not enough memory to create a new Integer" );
        return false ;
    }
    Parameter* newParam = new ( std::nothrow ) Parameter ( name, newInt );
    if ( newParam == NULL )
    {
        LOG_ERR ( "Not enough memory to create a new Parameter" );
        return false;
    }
    return addParameter ( newParam );
}

/**
 * Adds a double to the message
 */
bool Message::add ( const string& name, double value )
{
    Double* newDouble = new ( std::nothrow ) Double ( value );
    if ( NULL == newDouble )
    {
        LOG_ERR ( "Not enough memory to create a new Double" );
        return false ;
    }
    Parameter* newParam = new ( std::nothrow ) Parameter ( name, newDouble );
    if ( newParam == NULL )
    {
        LOG_ERR ( "Not enough memory to create a new Parameter" );
        return false;
    }
    return addParameter ( newParam );
}


/**
 * Add a string to the message
 */
bool Message::add ( const string& name, const char* value )
{
    String* newString = new ( std::nothrow ) String ( value );
    if ( NULL == newString )
    {
        LOG_ERR ( "Not enough memory to create a new String" );
        return false;
    }
    Parameter* newParam = new ( std::nothrow ) Parameter ( name, newString );
    if ( NULL == newParam )
    {
        LOG_ERR ( "Not enough memory to create a new Parameter" );
        return false;
    }
    return addParameter ( newParam );
}

/**
 * Add a float to the message
 */
bool Message::add ( const string& name, float value )
{
    Float* newFloat = new ( std::nothrow ) Float ( value );
    if ( NULL == newFloat )
    {
        LOG_ERR ( "Not enough memory to create a new Float" );
        return false;
    }
    Parameter* newParam = new ( std::nothrow )  Parameter ( name, newFloat );
    if ( NULL == newParam )
    {
        LOG_ERR ( "Not enough memory to create a new Parameter" );
        return false;
    }
    return addParameter ( newParam );
}

/**
 * Add a long to the message
 */
bool Message::add ( const string& name, long value )
{
    Long* newLong = new ( std::nothrow ) Long ( value );
    if ( NULL == newLong )
    {
        LOG_ERR ( "Not enough memory to create a new Long" );
        return false;
    }
    Parameter* newParam = new ( std::nothrow )  Parameter ( name, newLong );
    if ( NULL == newParam )
    {
        LOG_ERR ( "Not enough memory to create a new Parameter" );
        return false;
    }
    return addParameter ( newParam );
}

/**
 * Add a float to the message
 */
bool Message::add ( const string& name, bool value )
{
    Bool* newBool = new ( std::nothrow ) Bool ( value );
    if ( NULL == newBool )
    {
        LOG_ERR ( "Not enough memory to create a new Bool" );
        return false;
    }
    Parameter* newParam = new ( std::nothrow )  Parameter ( name, newBool );
    if ( NULL == newParam )
    {
        LOG_ERR ( "Not enough memory to create a new Parameter" );
        return false;
    }
    return addParameter ( newParam );
}

/**
 * Gets the string with the given name
 */
string Message::getString ( const string& stringName ) throw()
{
    return ObjImplMapper<Message, MessageImpl>::getImpl ( const_cast<Message*> ( this ) )->getString ( string ( stringName ) );
}

/**
 * Returns the int with the given name
 */
int Message::getInt ( const string& intName ) throw()
{
    return ObjImplMapper<Message, MessageImpl>::getImpl ( const_cast<Message*> ( this ) )->getInt ( string ( intName ) );
}

/**
 * Returns the float with the given name
 */
float Message::getFloat ( const string& floatName ) throw()
{
    return ObjImplMapper<Message, MessageImpl>::getImpl ( const_cast<Message*> ( this ) )->getFloat ( string ( floatName ) );
}

/**
 * Returns the bool's value with the given name
 */
bool Message::getBool ( const string& boolName ) throw()
{
    return ObjImplMapper<Message, MessageImpl>::getImpl ( const_cast<Message*> ( this ) )->getBool ( string ( boolName ) );
}

/**
 * Returns the long value with the given name
 */
long Message::getLong ( const string& longName ) throw()
{
    return ObjImplMapper<Message, MessageImpl>::getImpl ( const_cast<Message*> ( this ) )->getLong ( string ( longName ) );
}

/**
 * Returns the double value with the given name
 */
double Message::getDouble ( const string& doubleName ) throw()
{
    return ObjImplMapper<Message, MessageImpl>::getImpl ( const_cast<Message*> ( this ) )->getDouble ( string ( doubleName ) );
}

/**
 * Adds a parameter to the message
 */
bool Message::addParameter ( Parameter* param )
{
    ObjImplMapper<Message, MessageImpl>::getImpl ( const_cast<Message*> ( this ) )->addParameter ( param );
    return true;
}

/**
 * Returns the parameter with the given name
 */
Parameter& Message::operator [] ( const std::string& name )
{
    Parameter* parm = ObjImplMapper<Message, MessageImpl>::getImpl ( const_cast<Message*> ( this ) )->getParameter ( name );
    if ( NULL == parm )
    {
        parm = new Parameter ( name );
        addParameter ( parm );
    }
    return *parm;
}

/**
 * Returns the parameter with the given name, or throws an exception in case it was not found
 */
const Parameter& Message::operator [] ( const std::string& name ) const throw ( parameter_not_found )
{
    Parameter* parm = ObjImplMapper<Message, MessageImpl>::getImpl ( const_cast<Message*> ( this ) )->getParameter ( name );
    if ( NULL == parm )
    {
        throw parameter_not_found ( name );
    }
    return *parm;
}
