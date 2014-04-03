#include "ParameterImpl.h"
#include "SerializableObject.h"
#include "ObjectFactory.h"
#include "Parameter.h"
#include "ObjImplMapper.h"
#include "Logger.h"

string ParameterImpl:: TYPESTR_PARAMETER("PARAMETER");

ParameterImpl::ParameterImpl() : name(""), value(NULL)
{
}

ParameterImpl::ParameterImpl(const std::string &nm) : name(nm), value(NULL)
{
}

ParameterImpl::ParameterImpl(const std::string &nm, SerializableObject *val) : name(nm), value(val)
{
}


/**
 * Serializes this parameter
 */
string ParameterImpl::serialize()
{
string result = "<Parameter><Name>";
	result += name;
	result += "</Name><Type>";
	result += value->type();
	result += "</Type><Data>";
SERIALIZER serializer = ObjectFactory::getSerializer(value->type());
	result += serializer(value);
	result += "</Data></Parameter>";
	return result;	
}


/**
 * Deserializes the object from the given XML node from the given XML doc
 */
bool ParameterImpl::deserialize(xmlDocPtr doc, xmlNodePtr node)
{
xmlNodePtr nameNode = node->children;	// node containing the "Name" tag
xmlNodePtr typeNode = nameNode->next;	// node containing the "Type" tag
xmlNodePtr dataNode = typeNode->next;	// node containing the "Data" tag
xmlNodePtr contentNode = dataNode->children;	// node containing the "Content" Node, which has the implementation of the underlying object
	name = getXmlValue(doc, node, "Name");
string type = getXmlValue(doc, node, "Type");
DESERIALIZER objCreator = ObjectFactory::getDeserializer(type);
SerializableObject* newObj = objCreator(doc, contentNode);
	value = newObj;
	return true;
}

/**
 * CREATOR function to create a new Integer object from the given XML node in the given XML doc.
 * @param doc - the XML doc
 * @param node - is the Content node
 * @return a new Integer object
 */
Object* ParameterImpl::deserializeParameter(xmlDocPtr doc, xmlNodePtr node)
{
ParameterImpl* newValue = new(std::nothrow) ParameterImpl();
	if(NULL == newValue)
	{
		LOG_ERR("Not enough memory to create a new Parameter implementation");
		return NULL;
	}

	newValue->deserialize(doc, node);
Parameter* newParam = new(std::nothrow) Parameter(newValue->name, newValue->value);
	if(NULL == newParam)
	{
		LOG_ERR("Not enough memory to create a new Parameter");
		delete newValue;
		return NULL;
	}

	return newParam;
}

/**
 * Serializes the given integer value and returns its serialized form
 */
string ParameterImpl::serializeParameter(SerializableObject* parToSer)
{
Parameter* thePar = dynamic_cast<Parameter*>(parToSer);
	if(!thePar) return "";
	return ObjImplMapper<Parameter,ParameterImpl>::getImpl(thePar)->serialize();
}
