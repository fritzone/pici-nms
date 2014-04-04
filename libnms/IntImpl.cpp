#include "IntImpl.h"
#include "Logger.h"

#include <sstream>

using namespace std;


string IntImpl::TYPESTR_INTEGER ( "INT" );


IntImpl::IntImpl() : val ( 0 )
{

}

IntImpl::IntImpl ( int _val ) : val ( _val )
{

}

IntImpl::IntImpl ( const string& sv ) : val ( 0 )
{
    buildFromString ( sv ); // ignore the status, if it did not succeed, it'll be the default
}


/**
 * Serializes the object. Returns the serialized XML string, the Content node:
 * <Content>
 * <Value>
 *  the_int_value
 * </Value>
 * </Content>
 * @return the serialized Content XML
 */
string IntImpl::serialize()
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
bool IntImpl::deserialize ( const string& ser )
{
    return buildFromString ( ser );
}


/**
 * Deserializes the Integer from the node (which is the Content node)
 * @param doc - the XML document in which this integer is serialized
 * @param node - the Content node of the integer
 * @return true in case of success, false in case of failure
 */
bool IntImpl::deserialize ( xmlDocPtr doc , xmlNodePtr node )
{
    string valFromXml = getXmlValue ( doc, node, "Value" );
    return deserialize ( valFromXml );
}

/**
 * CREATOR function to create a new Integer object from the given XML node in the given XML doc.
 * @param doc - the XML doc
 * @param node - is the Content node
 * @return a new Integer object
 */
Object* IntImpl::deserializeInteger ( xmlDocPtr doc, xmlNodePtr node )
{
    IntImpl* newValue = new ( std::nothrow ) IntImpl();
    if ( NULL == newValue )
    {
        LOG_ERR ( "Not enough memory to create a integer implementation" );
        return NULL;
    }
    newValue->deserialize ( doc, node );
    Integer* newInt = new ( std::nothrow ) Integer ( newValue->val );
    if ( NULL == newInt )
    {
        LOG_ERR ( "Not enough memory to create a new integer" );
        delete newValue;
        return NULL;
    }
    return newInt;
}

/**
 * Serializes the given integer value and returns its serialized form
 */
string IntImpl::serializeInteger ( SerializableObject* intToSer )
{
    Integer* theInt = dynamic_cast<Integer*> ( intToSer );
    if ( !theInt )
    {
        return "";
    }
    return ObjImplMapper<Integer, IntImpl>::getImpl ( theInt )->serialize();
}

/**
 * Builds this object from the given string, returns the status of the operation: true if succeeded,
 * false if it did not succeed
 * @param ser - the string containing a serialized integer
 * @return true in case of success, false in case of a failure
 */
bool IntImpl::buildFromString ( const string& ser )
{
    istringstream iss ( ser );
    iss.setf ( ios::dec );
    return ! ( iss >> val ).fail();
}
