#include "BoolImpl.h"
#include "Logger.h"
#include "BoolWrapper.h"

string BoolImpl::TYPESTR_BOOL ( "BOOL" );

/**
 * Constructor
 */
BoolImpl::BoolImpl() : val ( false )
{
}

/**
 * Constructor
 */
BoolImpl::BoolImpl ( bool _val ) : val ( _val )
{
}

/**
 * Constructor
 */
BoolImpl::BoolImpl ( const string& _sval ) : val ( 0 )
{
    buildFromString ( _sval );
}

/**
 * Builds the bool from the string
 */
bool BoolImpl::buildFromString ( const std::string& str )
{
    val = false;
    if ( "true" == str )
    {
        val = true;
        return true;
    }
    if ( "false" == str )
    {
        return true;
    }
    return false;
}

/**
 * Serializes the object. Returns the serialized XML string, the Content node:
 * <Content>
 * <Value>
 *  the_bool_value
 * </Value>
 * </Content>
 * @return the serialized Content XML
 */
string BoolImpl::serialize()
{
    string result = "<Content><Value>";
    result += val ? "true" : "false";
    result += "</Value></Content>";
    return result;
}


/**
 * Deserializes this object from the given string. The string should be a plain number, NOT XML
 * @param ser - the number, as a string
 * @return ture in case of success, false in case of failure
 */
bool BoolImpl::deserialize ( const string& ser )
{
    return buildFromString ( ser );
}

/**
 * Deserializes the Bool from the node (which is the Content node)
 * @param doc - the XML document in which this Bool is serialized
 * @param node - the Content node of the Bool
 * @return true in case of success, false in case of failure
 */
bool BoolImpl::deserialize ( xmlDocPtr doc , xmlNodePtr node )
{
    string valFromXml = getXmlValue ( doc, node, "Value" );
    return deserialize ( valFromXml );
}

/**
 * CREATOR function to create a new Bool object from the given XML node in the given XML doc.
 * @param doc - the XML doc
 * @param node - is the Content node
 * @return a new Bool object
 */
Object* BoolImpl::deserializeBool ( xmlDocPtr doc, xmlNodePtr node )
{
    BoolImpl* newValue = new ( std::nothrow ) BoolImpl();
    if ( NULL == newValue )
    {
        LOG_ERR ( "Not enough memory to create a new BoolImpl" );
        return NULL;
    }
    newValue->deserialize ( doc, node );
    Bool* newBool = new ( std::nothrow ) Bool ( newValue->val );
    if ( NULL == newBool )
    {
        LOG_ERR ( "Not enough memory to create a new Bool" );
        delete newValue;
        return NULL;
    }
    return newBool;
}

/**
 * Serializes the given Bool value and returns its serialized form
 */
string BoolImpl::serializeBool ( SerializableObject* BoolToSer )
{
    Bool* theBool = dynamic_cast<Bool*> ( BoolToSer );
    if ( !theBool )
    {
        return "";
    }
    return ObjImplMapper<Bool, BoolImpl>::getImpl ( theBool )->serialize();
}

