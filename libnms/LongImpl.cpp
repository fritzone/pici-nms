#include "LongImpl.h"

#include "Logger.h"

#include <sstream>

using namespace std;

string LongImpl::TYPESTR_LONG ( "LONG" );

/**
 * Constructor
 */
LongImpl::LongImpl() : val ( 0 )
{
}

/**
 * Constructor
 */
LongImpl::LongImpl ( long _val ) : val ( _val )
{
}

/**
 * Constructor
 */
LongImpl::LongImpl ( const string& _sval ) : val ( 0 )
{
    buildFromString ( _sval );
}

/**
 * Builds the Long from the string
 */
bool LongImpl::buildFromString ( const std::string& str )
{
    istringstream iss ( str );
    iss.setf ( ios::dec );
    return ! ( iss >> val ).fail();

}

/**
 * Serializes the object. Returns the serialized XML string, the Content node:
 * <Content>
 * <Value>
 *  the_Long_value
 * </Value>
 * </Content>
 * @return the serialized Content XML
 */
string LongImpl::serialize()
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
bool LongImpl::deserialize ( const string& ser )
{
    return buildFromString ( ser );
}

/**
 * Deserializes the Long from the node (which is the Content node)
 * @param doc - the XML document in which this Long is serialized
 * @param node - the Content node of the Long
 * @return true in case of success, false in case of failure
 */
bool LongImpl::deserialize ( xmlDocPtr doc , xmlNodePtr node )
{
    string valFromXml = getXmlValue ( doc, node, "Value" );
    return deserialize ( valFromXml );
}

/**
 * CREATOR function to create a new Long object from the given XML node in the given XML doc.
 * @param doc - the XML doc
 * @param node - is the Content node
 * @return a new Long object
 */
Object* LongImpl::deserializeLong ( xmlDocPtr doc, xmlNodePtr node )
{
    LongImpl* newValue = new ( std::nothrow ) LongImpl();
    if ( NULL == newValue )
    {
        LOG_ERR ( "Cannot create a new Long implementation" );
        return NULL;
    }
    newValue->deserialize ( doc, node );
    Long* newLong = new ( std::nothrow ) Long ( newValue->val );
    if ( NULL == newLong )
    {
        LOG_ERR ( "Cannot create a new long object" );
        delete newValue;
        return NULL;
    }
    return newLong;
}

/**
 * Serializes the given Long value and returns its serialized form
 */
string LongImpl::serializeLong ( SerializableObject* LongToSer )
{
    Long* theLong = dynamic_cast<Long*> ( LongToSer );
    if ( !theLong )
    {
        return "";
    }
    return ObjImplMapper<Long, LongImpl>::getImpl ( theLong )->serialize();
}

