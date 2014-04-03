#ifndef _LONG_IMPL_H_
#define _LONG_IMPL_H_

#include "xml_handler.h"
#include "LongWrapper.h"
#include "ObjImplMapper.h"

#include <string>
using namespace std;

/**
 * Class representing the implementation of an Long
 */
class LongImpl
{
public:

	/**
	 * Default constructor, initializes the value to 0
	 */
	LongImpl();	
	
	/**
	 * Constructor, initializes the value to the given _val
	 */
	LongImpl(long _val);

	/**
	 * Constructor. Buidls the object from the given string.
	 */
	LongImpl(const string& sv);

	/**
	 * Serializes the object. Returns the serialized XML string, the Content node:
	 * <Content>
	 * <Value>
	 *  the_Long_value
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
	 * Deserializes the Long from the node (which is the Content node)
	 * @param doc - the XML document in which this Long is serialized
	 * @param node - the Content node of the Long
	 * @return true in case of success, false in case of failure
	 */
	bool deserialize(xmlDocPtr doc ,xmlNodePtr node);

	/**
	 * Builds this object from the given string, returns the status of the operation: true if succeeded,
	 * false if it did not succeed
	 * @param ser - the string containing a serialized Long
	 * @return true in case of success, false in case of a failure
	 */
	bool buildFromString(const string& ser);

	/**
	 * Returns the value of this Long as an Long value
	 * @return the value of the object
	 */
	long getValue() const
	{
		return val;
	}

public:

	/**
	 * CREATOR function to create a new Long object from the given XML node in the given XML doc.
	 * @param doc - the XML doc
	 * @param node - is the Content node
	 * @return a new Long object
	 */
	static Object* deserializeLong(xmlDocPtr doc, xmlNodePtr node);

	/**
	 * SERIALIZER function.
	 * Serializes the given object to a string that can be sent over the wire
	 */
	static string serializeLong(SerializableObject* LongToSer);

private:

	// the value of this Long
	long val;

public:

	static string TYPESTR_LONG;

};

#endif
