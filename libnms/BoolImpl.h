#ifndef _BOOL_IMPL_H_
#define _BOOL_IMPL_H_

#include "xml_handler.h"
#include "BoolWrapper.h"
#include "ObjImplMapper.h"

#include <string>
using namespace std;


/**
 * Implementation class for a Bool
 */
class BoolImpl
{

public:
    /**
     * Default constructor, initializes the value to false
     */
    BoolImpl();

    /**
     * Constructor, initializes the value to the given _val
     */
    BoolImpl ( bool _val );

    /**
     * Constructor. Builds the object from the given string.
     */
    BoolImpl ( const string& sv );

    /**
     * Serializes the object. Returns the serialized XML string, the Content node:
     * <Content>
     * <Value>
     *  the_Bool_value
     * </Value>
     * </Content>
     * @return the serialized Content XML
     */
    string serialize();

    /**
     * Deserializes this object from the given string. The string should be plain string, NOT XML
     * @param ser - the number, as a string
     * @return true in case of success, false in case of failure
     */
    bool deserialize ( const string& ser );

    /**
     * Deserializes the Bool from the node (which is the Content node)
     * @param doc - the XML document in which this Bool is serialized
     * @param node - the Content node of the Bool
     * @return true in case of success, false in case of failure
     */
    bool deserialize ( xmlDocPtr doc , xmlNodePtr node );

    bool getValue() const
    {
        return val;
    }

public:

    /**
     * CREATOR function to create a new Bool object from the given XML node in the given XML doc.
     * @param doc - the XML doc
     * @param node - is the Content node
     * @return a new Integer object
     */
    static Object* deserializeBool ( xmlDocPtr doc, xmlNodePtr node );

    /**
     * SERIALIZER function.
     * Serializes the given object to a string that can be sent over the wire
     */
    static string serializeBool ( SerializableObject* boolToSer );

private:

    /**
     * Builds this bool
     */
    bool buildFromString ( const string& str );

private:

    // the actual value of the bool
    bool val;

public:

    static string TYPESTR_BOOL;

};

#endif

