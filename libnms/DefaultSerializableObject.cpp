#include "DefaultSerializableObject.h"

string DefaultSerializableObject::serialize()
{
    return string ( "" );
}

bool DefaultSerializableObject::deserialize ( const string& )
{
    return false;
}

