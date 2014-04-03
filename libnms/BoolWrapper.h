#ifndef _BOOL_WRAPPER_H_
#define _BOOL_WRAPPER_H_

#include "DefaultSerializableObject.h"

/**
 * Wrapper class to allow serialization of boolean (bool) values. Also, provides methods for converting
 * boolean values to string and vice-versa.
 */
class Bool : public DefaultSerializableObject
{
public:

	/**
	 * Constructs a new Bool object, sets the value to default false.
	 */
	Bool();

	/**
	 * Constructs a new Bool object, setting the value to the parameter.
	 * @param _val - the new value of the bool
	 */
	Bool(bool _val);

	/**
	 * Constructs a new Bool value from the given string.
	 * @param _sval - the string (either "true" or "false")
	 */
	Bool(const string& _sval);

	/**
	 * Destructor
	 */
	~Bool();

	/**
	 * Default casting of the Bool to a bool value
	 */
	operator bool () const ;

	/**
	 * Returns the type description of the Bool class. 
	 * @return the type description of the Bool class
	 */
	virtual const string& type() const;

	/**
	 * Returns a string representation of the Bool object
	 */
	virtual const string toString() const;

};

#endif
