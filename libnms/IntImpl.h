#ifndef _INT_IMPL_H_
#define _INT_IMPL_H_

#include "xml_handler.h"
#include "IntWrapper.h"
#include "ObjImplMapper.h"

#include <string>
using namespace std;

/**
 * Class representing the implementation of an integer
 */
class IntImpl
{
public:

	/**
	 * Default constructor, initializes the value to 0
	 */
	IntImpl();	
	
	/**
	 * Constructor, initializes the value to the given _val
	 */
	IntImpl(int _val);

	/**
	 * Constructor. Buidls the object from the given string.
	 */
	IntImpl(const string& sv);

	/**
	 * Serializes the object. Returns the serialized XML string, the Content node:
	 * <Content>
	 * <Value>
	 *  the_int_value
	 * </Value>
	 * </Content>
	 * @return the serialized Content XML
	 */
	string serialize();

	/**
	 * Deserializes this object from the given string. The string should be a plain number, NOT XML
	 * @param ser - the number, as a string
	 * @return ture in case of success, false in case of failure
	 */
	bool deserialize(const string& ser);

	/**
	 * Deserializes the Integer from the node (which is the Content node)
	 * @param doc - the XML document in which this integer is serialized
	 * @param node - the Content node of the integer
	 * @return true in case of success, false in case of failure
	 */
	bool deserialize(xmlDocPtr doc ,xmlNodePtr node);

	/**
	 * Builds this object from the given string, returns the status of the operation: true if succeeded,
	 * false if it did not succeed
	 * @param ser - the string containing a serialized integer
	 * @return true in case of success, false in case of a failure
	 */
	bool buildFromString(const string& ser);

	/**
	 * Returns the value of this integer as an integer value
	 * @return the value of the object
	 */
	int getValue() const
	{
		return val;
	}

public:

	/**
	 * CREATOR function to create a new Integer object from the given XML node in the given XML doc.
	 * @param doc - the XML doc
	 * @param node - is the Content node
	 * @return a new Integer object
	 */
	static Object* deserializeInteger(xmlDocPtr doc, xmlNodePtr node);

	/**
	 * SERIALIZER function.
	 * Serializes the given object to a string that can be sent over the wire
	 */
	static string serializeInteger(SerializableObject* intToSer);

private:

	// the value of this integer
	int val;

public:

	static string TYPESTR_INTEGER;

};

#endif
