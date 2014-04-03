#ifndef _FLOAT_IMPL_H_
#define _FLOAT_IMPL_H_

#include "xml_handler.h"
#include "FloatWrapper.h"
#include "Object.h"
#include "ObjImplMapper.h"

#include <string>
using namespace std;

/**
 * Implementation class for a float
 */
class FloatImpl
{

public:
	/**
	 * Default constructor, initializes the value to 0
	 */
	FloatImpl();	
	
	/**
	 * Constructor, initializes the value to the given _val
	 */
	FloatImpl(float _val);

	/**
	 * Constructor. Builds the object from the given string.
	 */
	FloatImpl(const string& sv);

	/**
	 * Serializes the object. Returns the serialized XML string, the Content node:
	 * <Content>
	 * <Value>
	 *  the_Float_value
	 * </Value>
	 * </Content>
	 * @return the serialized Content XML
	 */
	string serialize();

	/**
	 * Deserializes this object from the given string. The string should be a plain number, NOT XML
	 * @param ser - the number, as a string
	 * @return true in case of success, false in case of failure
	 */
	bool deserialize(const string& ser);

	/**
	 * Deserializes the Float from the node (which is the Content node)
	 * @param doc - the XML document in which this Float is serialized
	 * @param node - the Content node of the Float
	 * @return true in case of success, false in case of failure
	 */
	bool deserialize(xmlDocPtr doc ,xmlNodePtr node);

	float getValue() const
	{
		return val;
	}

public:

	/**
	 * CREATOR function to create a new Float object from the given XML node in the given XML doc.
	 * @param doc - the XML doc
	 * @param node - is the Content node
	 * @return a new Integer object
	 */
	static Object* deserializeFloat(xmlDocPtr doc, xmlNodePtr node);

	/**
	 * SERIALIZER function.
	 * Serializes the given object to a string that can be sent over the wire
	 */
	static string serializeFloat(SerializableObject* floatToSer);

private:

	/**
	 * Builds this float 
	 */
	bool buildFromString(const string& str);

private:

	// the actual value of the float
	float val;

public:

	static string TYPESTR_FLOAT;

};

#endif
