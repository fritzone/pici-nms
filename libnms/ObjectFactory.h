#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

#include "xml_handler.h"
#include "SerializableObject.h"

#include <map>
#include <string>

// these methods create objects from the given xml node and doc
typedef SerializableObject* ( *DESERIALIZER ) ( xmlDocPtr, xmlNodePtr );

// these methods serialize a serializable object into the required string form
typedef std::string ( *SERIALIZER ) ( SerializableObject* );

class ObjectFactory
{
public:

    /**
     * Maps a creator for the given type to the given method. Used when we're deserializing a
     * serialized object
     */
    static void mapDeserializer ( const std::string& name, DESERIALIZER method )
    {
        creators.insert ( make_pair<std::string, DESERIALIZER> ( name, method ) );
    }

    /**
     * Returns the createor method of the given type
     */
    static DESERIALIZER getDeserializer ( const std::string& name )
    {
        return creators.find ( name )->second;
    }

    static void mapSerializer ( const std::string& name, SERIALIZER method )
    {
        serializers.insert ( make_pair<string, SERIALIZER> ( name, method ) );
    }

    static SERIALIZER getSerializer ( const std::string& name )
    {
        return serializers.find ( name )->second;
    }

private:

    // holds the creators mapped to the TYPENAME they create
    static map<std::string, DESERIALIZER> creators;

    // maps the serializer methods to the given type
    static map<std::string, SERIALIZER> serializers;
};

#endif
