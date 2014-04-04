#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

#include "xml_handler.h"
#include "SerializableObject.h"

#include <map>
#include <string>

using namespace std;

// these methods create objects from the given xml node and doc
typedef SerializableObject* ( *DESERIALIZER ) ( xmlDocPtr, xmlNodePtr );

// these methods serialize a serializable object into the required string form
typedef string ( *SERIALIZER ) ( SerializableObject* );

class ObjectFactory
{
public:

    /**
     * Maps a creator for the given type to the given method. Used when we're deserializing a
     * serialized object
     */
    static void mapDeserializer ( const string& name, DESERIALIZER method )
    {
        creators.insert ( make_pair<string, DESERIALIZER> ( name, method ) );
    }

    /**
     * Returns the createor method of the given type
     */
    static DESERIALIZER getDeserializer ( const string& name )
    {
        return creators.find ( name )->second;
    }

    static void mapSerializer ( const string& name, SERIALIZER method )
    {
        serializers.insert ( make_pair<string, SERIALIZER> ( name, method ) );
    }

    static SERIALIZER getSerializer ( const string& name )
    {
        return serializers.find ( name )->second;
    }

private:

    // holds the creators mapped to the TYPENAME they create
    static map<string, DESERIALIZER> creators;

    // maps the serializer methods to the given type
    static map<string, SERIALIZER> serializers;
};

#endif
