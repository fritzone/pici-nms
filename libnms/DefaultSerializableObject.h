#ifndef _DEFAULT_SERIALIZBALE_BOJECT_H_
#define _DEFAULT_SERIALIZBALE_BOJECT_H_

#include "SerializableObject.h"

#include<string>

using namespace std;

/**
 * A very basic class for defining serializable objects
 */
class DefaultSerializableObject : public SerializableObject
{
public:
    /**
     * Serializes this object, providing a way to send it over the network
     */
    virtual string serialize();

    /**
     * De-serializes this object, reconstructing from the data that was sent over the network
     * @param ser - the serialized string, containing just the serialized form of the object, without the XML tags
     * @return true in case of success, false in case of failure
     */
    virtual bool deserialize ( const string& ser );

};

#endif
