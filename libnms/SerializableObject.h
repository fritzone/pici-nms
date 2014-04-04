#ifndef _SERIALIZABLE_OBJECT_H_
#define _SERIALIZABLE_OBJECT_H_

#include "Object.h"
#include "apidef.h"

#include <string>

using namespace std;

class MessageDigest;
class ObjectSerializer;

/**
 * Abstract class representing an object which can be serialized
 */
class LIBNMS_API SerializableObject : public Object
{
public:

    /**
     * COnstructor
     */
    SerializableObject()
    {
    }

    /**
     * Destructor
     */
    ~SerializableObject()
    {
    }

    /**
     * Serializes this object, providing a way to send it over the network
     */
    virtual string serialize() = 0;

    /**
     * De-serializes this object, reconstructing from the data that was sent over the network
     * @param ser - the serialized string, containing just the serialized form of the object, without the XML tags
     * @return true in case of success, false in case of failure
     */
    virtual bool deserialize ( const string& ser ) = 0;

    /**
     * Returns the type of the data as a string that can be put into the XML without too much complication
     */
    virtual const string& type() const = 0;

    /**
     * Return a hash code for this object
     */
    virtual string getHashCode();

};

#endif
