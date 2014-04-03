#include "ObjectFactory.h"

map<string, DESERIALIZER> ObjectFactory::creators;
map<string, SERIALIZER> ObjectFactory::serializers;