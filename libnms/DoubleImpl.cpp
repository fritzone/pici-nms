#include "DoubleImpl.h"
#include "Logger.h"

#include <sstream>

using namespace std;

string DoubleImpl::TYPESTR_DOUBLE ( "DOUBLE" );

/**
 * Constructor
 */
DoubleImpl::DoubleImpl() : val ( 0.0F )
{
}

/**
 * Constructor
 */
DoubleImpl::DoubleImpl ( double _val ) : val ( _val )
{
}

/**
 * Constructor
 */
DoubleImpl::DoubleImpl ( const string& _sval ) : val ( 0 )
{
    buildFromString ( _sval );
}

/**
 * Builds the double from the string
 */
bool DoubleImpl::buildFromString ( const std::string& str )
{
    istringstream iss ( str );
    iss.setf ( ios::dec );
    return ! ( iss >> val ).fail();

}

/**
 * Serializes the object. Returns the serialized XML string, the Content node:
 * <Content>
 * <Value>
 *  the_double_value
 * </Value>
 * </Content>
 * @return the serialized Content XML
 */
string DoubleImpl::serialize()
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
bool DoubleImpl::deserialize ( const string& ser )
{
    return buildFromString ( ser );
}

/**
 * Deserializes the Double from the node (which is the Content node)
 * @param doc - the XML document in which this Double is serialized
 * @param node - the Content node of the Double
 * @return true in case of success, false in case of failure
 */
bool DoubleImpl::deserialize ( xmlDocPtr doc , xmlNodePtr node )
{
    string valFromXml = getXmlValue ( doc, node, "Value" );
    return deserialize ( valFromXml );
}

/**
 * CREATOR function to create a new Double object from the given XML node in the given XML doc.
 * @param doc - the XML doc
 * @param node - is the Content node
 * @return a new Double object
 */
Object* DoubleImpl::deserializeDouble ( xmlDocPtr doc, xmlNodePtr node )
{
    DoubleImpl* newValue = new ( std::nothrow ) DoubleImpl();
    if ( NULL == newValue )
    {
        LOG_ERR ( "Not enough memory to create a double implementation" );
        return NULL;
    }
    newValue->deserialize ( doc, node );
    Double* newDouble = new ( std::nothrow ) Double ( newValue->val );
    if ( NULL == newDouble )
    {
        LOG_ERR ( "Not enough memory to create a double" );
        delete newValue;
        return NULL;
    }
    return newDouble;
}

/**
 * Serializes the given Double value and returns its serialized form
 */
string DoubleImpl::serializeDouble ( SerializableObject* DoubleToSer )
{
    Double* theDouble = dynamic_cast<Double*> ( DoubleToSer );
    if ( !theDouble )
    {
        return "";
    }
    return ObjImplMapper<Double, DoubleImpl>::getImpl ( theDouble )->serialize();
}

