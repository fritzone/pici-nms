#ifndef _CHAR_IMPL_H_
#define _CHAR_IMPL_H_

#include "xml_handler.h"
#include "CharWrapper.h"
#include "ObjImplMapper.h"

#include <string>
using namespace std;


/**
 * Implementation class for a Char
 */
class CharImpl
{

public:
    /**
     * Default constructor, initializes the value to false
     */
    CharImpl();

    /**
     * Constructor, initializes the value to the given _val
     */
    CharImpl ( char _val );

    /**
     * Constructor. Builds the object from the given string.
     */
    CharImpl ( const string& sv );

    /**
     * Serializes the object. Returns the serialized XML string, the Content node:
     * <Content>
     * <Value>
     *  the_Char_value
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
     * Deserializes the Char from the node (which is the Content node)
     * @param doc - the XML document in which this Char is serialized
     * @param node - the Content node of the Char
     * @return true in case of success, false in case of failure
     */
    bool deserialize ( xmlDocPtr doc , xmlNodePtr node );

    char getValue() const
    {
        return val;
    }

public:

    /**
     * CREATOR function to create a new Char object from the given XML node in the given XML doc.
     * @param doc - the XML doc
     * @param node - is the Content node
     * @return a new Integer object
     */
    static Object* deserializeChar ( xmlDocPtr doc, xmlNodePtr node );

    /**
     * SERIALIZER function.
     * Serializes the given object to a string that can be sent over the wire
     */
    static string serializeChar ( SerializableObject* charToSer );

private:

    /**
     * Builds this char
     */
    bool buildFromString ( const string& str );

private:

    // the actual value of the char
    char val;

public:

    static string TYPESTR_CHAR;

};

#endif

