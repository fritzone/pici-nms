#include "FloatImpl.h"
#include "Logger.h"

#include <sstream>

using namespace std;

string FloatImpl::TYPESTR_FLOAT ( "FLOAT" );

/**
 * Constructor
 */
FloatImpl::FloatImpl() : val ( 0.0F )
{
}

/**
 * Constructor
 */
FloatImpl::FloatImpl ( float _val ) : val ( _val )
{
}

/**
 * Constructor
 */
FloatImpl::FloatImpl ( const string& _sval ) : val ( 0 )
{
    buildFromString ( _sval );
}

/**
 * Builds the float from the string
 */
bool FloatImpl::buildFromString ( const std::string& str )
{
    istringstream iss ( str );
    iss.setf ( ios::dec );
    return ! ( iss >> val ).fail();

}

/**
 * Serializes the object. Returns the serialized XML string, the Content node:
 * <Content>
 * <Value>
 *  the_float_value
 * </Value>
 * </Content>
 * @return the serialized Content XML
 */
string FloatImpl::serialize()
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
bool FloatImpl::deserialize ( const string& ser )
{
    return buildFromString ( ser );
}

/**
 * Deserializes the Float from the node (which is the Content node)
 * @param doc - the XML document in which this Float is serialized
 * @param node - the Content node of the Float
 * @return true in case of success, false in case of failure
 */
bool FloatImpl::deserialize ( xmlDocPtr doc , xmlNodePtr node )
{
    string valFromXml = getXmlValue ( doc, node, "Value" );
    return deserialize ( valFromXml );
}

/**
 * CREATOR function to create a new Float object from the given XML node in the given XML doc.
 * @param doc - the XML doc
 * @param node - is the Content node
 * @return a new Float object
 */
Object* FloatImpl::deserializeFloat ( xmlDocPtr doc, xmlNodePtr node )
{
    FloatImpl* newValue = new ( std::nothrow ) FloatImpl();
    if ( NULL == newValue )
    {
        LOG_ERR ( "Not enough memory to create a float implementation" );
        return NULL;
    }
    newValue->deserialize ( doc, node );
    Float* newFloat = new ( std::nothrow ) Float ( newValue->val );
    if ( NULL == newFloat )
    {
        LOG_ERR ( "Not enough memory to create a float" );
        delete newValue;
        return NULL;
    }
    return newFloat;
}

/**
 * Serializes the given Float value and returns its serialized form
 */
string FloatImpl::serializeFloat ( SerializableObject* FloatToSer )
{
    Float* theFloat = dynamic_cast<Float*> ( FloatToSer );
    if ( !theFloat )
    {
        return "";
    }
    return ObjImplMapper<Float, FloatImpl>::getImpl ( theFloat )->serialize();
}

