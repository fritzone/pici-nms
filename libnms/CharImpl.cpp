#include "CharImpl.h"
#include "Logger.h"

#include <sstream>

using namespace std;

string CharImpl::TYPESTR_CHAR ( "CHAR" );

/**
 * Constructor
 */
CharImpl::CharImpl() : val ( 0 )
{
}

/**
 * Constructor
 */
CharImpl::CharImpl ( char _val ) : val ( _val )
{
}

/**
 * Constructor
 */
CharImpl::CharImpl ( const string& _sval ) : val ( 0 )
{
    buildFromString ( _sval );
}

/**
 * Builds the char from the string
 */
bool CharImpl::buildFromString ( const std::string& str )
{
    istringstream iss ( str );
    iss.setf ( ios::dec );
    return ! ( iss >> val ).fail();

}

/**
 * Serializes the object. Returns the serialized XML string, the Content node:
 * <Content>
 * <Value>
 *  the_char_value
 * </Value>
 * </Content>
 * @return the serialized Content XML
 */
string CharImpl::serialize()
{
    stringstream ss;
    ss  << val;
    string result = "<Content><Value>";
    result += ss.str();
    result += "</Value></Content>";
    return result;
}


/**
 * Deserializes this object from the given string. The string should be a plain number, NOT XML
 * @param ser - the number, as a string
 * @return ture in case of success, false in case of failure
 */
bool CharImpl::deserialize ( const string& ser )
{
    return buildFromString ( ser );
}

/**
 * Deserializes the Char from the node (which is the Content node)
 * @param doc - the XML document in which this Char is serialized
 * @param node - the Content node of the Char
 * @return true in case of success, false in case of failure
 */
bool CharImpl::deserialize ( xmlDocPtr doc , xmlNodePtr node )
{
    string valFromXml = getXmlValue ( doc, node, "Value" );
    return deserialize ( valFromXml );
}

/**
 * CREATOR function to create a new Char object from the given XML node in the given XML doc.
 * @param doc - the XML doc
 * @param node - is the Content node
 * @return a new Char object
 */
Object* CharImpl::deserializeChar ( xmlDocPtr doc, xmlNodePtr node )
{
    CharImpl* newValue = new ( std::nothrow ) CharImpl();
    if ( NULL == newValue )
    {
        LOG_ERR ( "Not enough memory to create a char implementation" );
        return NULL;
    }
    newValue->deserialize ( doc, node );
    Char* newChar = new ( std::nothrow ) Char ( newValue->val );
    if ( NULL == newChar )
    {
        LOG_ERR ( "Not enough memory to create a char" );
        delete newValue;
        return NULL;
    }
    return newChar;
}

/**
 * Serializes the given Char value and returns its serialized form
 */
string CharImpl::serializeChar ( SerializableObject* CharToSer )
{
    Char* theChar = dynamic_cast<Char*> ( CharToSer );
    if ( !theChar )
    {
        return "";
    }
    return ObjImplMapper<Char, CharImpl>::getImpl ( theChar )->serialize();
}

