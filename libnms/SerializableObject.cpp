#include "SerializableObject.h"
#include "MessageDigest.h"

/**
 * Returns an SHA1 hashcode for the object
 */
string SerializableObject::getHashCode()
{
    return MessageDigest::getHashCode ( serialize() );
}