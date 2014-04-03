#ifndef _PARAMETER_IMPL_H_
#define _PARAMETER_IMPL_H_

#include <string>

#include "xml_handler.h"
#include "Object.h"

using namespace std;

class SerializableObject;

/**
 * Inner Implementation of a parameter
 */
class ParameterImpl 
{
public:

	/**
	 * Creates a new implementation object
	 */
	ParameterImpl();

	/**
	 * Creates a new parameter implementation with the given name
	 */
	ParameterImpl(const string& nm);

	/**
	 * Creates a new parameter implementation with the given name and value
	 */
	ParameterImpl(const string& nm, SerializableObject* val);

	/**
	 * Serializes this parameter in the following XML format:
	 * <Parameter>
	 *  <Name> NAME </Name>
	 *  <Type> TYPE </Type>
	 *  <Data> serialized value of the parameter, starting from a "Context" node </Data>
	 * </Parameter>
	 * @return the serialized parameter
	 */
	string serialize();

	/**
	 * Deserializes the object from the given string
	 * @param ser - the serialized XML form of the parameter
	 * @return true in case of success, false in case of failure
	 */
	bool deserialize(const string& ser);

	/**
	 * Deserializes the Object from the node (which is the Content node)
	 * @param doc - the XML document in which this integer is serialized
	 * @param node - the Content node of the integer
	 * @return true in case of success, false in case of failure
	 */
	bool deserialize(xmlDocPtr doc ,xmlNodePtr node);

	/**
	 * Returns the value of the parameter
	 * @return the value of the parameter
	 */
	SerializableObject* getValue() const
	{
		return value;
	}

	/**
	 * Returns the name of the parameter
	 * @return the name of the parameter
	 */
	const string& getName() const
	{
		return name;
	}

	/**
	 * Sets the value of this object
	 */
	void setValue(SerializableObject* so)
	{
		value = so;
	}

public:

	
	/**
	 * DESERIALIZER function to create a new Parameter object from the given XML node in the given XML doc.
	 * @param doc - the XML doc
	 * @param node - is the Content node
	 * @return a new Integer object
	 */
	static Object* deserializeParameter(xmlDocPtr doc, xmlNodePtr node);

	/**
	 * SERIALIZER function to serialize one parameter object (transmitted in the parToSer parameter)
	 */
	static string serializeParameter(SerializableObject* parToSer);

private:

	// the name of the parameter
	string name;

	// the value of the parameter
	SerializableObject* value;

public:

	static string TYPESTR_PARAMETER;

	friend class Parameter;
};

#endif
