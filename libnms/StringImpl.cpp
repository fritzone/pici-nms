#include "StringImpl.h"
#include "StringWrapper.h"
#include "Logger.h"

string StringImpl::TYPESTR_STRING ( "STRING" );

/**
 * Constructor
 */
StringImpl::StringImpl() : val ( "" )
{
}

/**
 * Constructor
 */
StringImpl::StringImpl ( const char* _val ) : val ( _val )
{
}

/**
 * Constructor
 */
StringImpl::StringImpl ( const string& _sval ) : val ( _sval )
{
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
string StringImpl::serialize()
{
    string result = "<Content><Value>";
    result += val;
    result += "</Value></Content>";
    return result;
}


/**
 * Deserializes this object from the given string. The string should be a plain string, NOT XML
 * @param ser - the number, as a string
 * @return ture in case of success, false in case of failure
 */
bool StringImpl::deserialize ( const string& ser )
{
    val = ser;
    return true;
}

/**
 * Deserializes the String from the node (which is the Content node)
 * @param doc - the XML document in which this String is serialized
 * @param node - the Content node of the String
 * @return true in case of success, false in case of failure
 */
bool StringImpl::deserialize ( xmlDocPtr doc , xmlNodePtr node )
{
    string valFromXml = getXmlValue ( doc, node, "Value" );
    return deserialize ( valFromXml );
}

/**
 * CREATOR function to create a new String object from the given XML node in the given XML doc.
 * @param doc - the XML doc
 * @param node - is the Content node
 * @return a new String object
 */
Object* StringImpl::deserializeString ( xmlDocPtr doc, xmlNodePtr node )
{
    StringImpl* newValue = new ( std::nothrow ) StringImpl();
    if ( NULL == newValue )
    {
        LOG_ERR ( "Not enough memory to create a String implementation" );
        return NULL;
    }
    newValue->deserialize ( doc, node );
    String* newString = new ( std::nothrow ) String ( newValue->val );
    if ( NULL == newString )
    {
        LOG_ERR ( "Not enough memory to create a String" );
        delete newValue;
        return NULL;
    }
    return newString;
}

/**
 * Serializes the given String value and returns its serialized form
 */
string StringImpl::serializeString ( SerializableObject* StringToSer )
{
    String* theString = dynamic_cast<String*> ( StringToSer );
    if ( !theString )
    {
        return "";
    }
    return ObjImplMapper<String, StringImpl>::getImpl ( theString )->serialize();
}

