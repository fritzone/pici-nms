#ifndef _STRING_IMPL_H_
#define _STRING_IMPL_H_

#include "xml_handler.h"
#include "ObjImplMapper.h"
#include "SerializableObject.h"

#include <string>

/**
 * Implementation class for a String
 */
class StringImpl
{

public:
    /**
     * Default constructor, initializes the value to false
     */
    StringImpl();

    /**
     * Constructor, initializes the value to the given _val
     */
    StringImpl ( const char* _val );

    /**
     * Constructor. Builds the object from the given string.
     */
    StringImpl ( const std::string& sv );

    /**
     * Serializes the object. Returns the serialized XML string, the Content node:
     * <Content>
     * <Value>
     *  the_String_value
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
    bool deserialize ( const std::string& ser );

    /**
     * Deserializes the String from the node (which is the Content node)
     * @param doc - the XML document in which this String is serialized
     * @param node - the Content node of the String
     * @return true in case of success, false in case of failure
     */
    bool deserialize ( xmlDocPtr doc , xmlNodePtr node );

    const std::string& getValue() const
    {
        return val;
    }

public:

    /**
     * CREATOR function to create a new String object from the given XML node in the given XML doc.
     * @param doc - the XML doc
     * @param node - is the Content node
     * @return a new Integer object
     */
    static Object* deserializeString ( xmlDocPtr doc, xmlNodePtr node );

    /**
     * SERIALIZER function.
     * Serializes the given object to a string that can be sent over the wire
     */
    static std::string serializeString ( SerializableObject* stringToSer );

private:

    // the actual value of the String
    std::string val;

public:

    static std::string TYPESTR_STRING;

};

#endif

