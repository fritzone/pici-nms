#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "DefaultSerializableObject.h"

#include <string>

using namespace std;

/**
 * Basic abstract class for representing a Number
 */
class Number : public DefaultSerializableObject
{
public:

	/**
	 * Returns the type of the data as a string that can be put into the XML without too much complication
	 */
	virtual const string& type() const = 0;

	/**
	 * Returns a string representation of the given number
	 */
	virtual const string toString() const = 0;

};

#endif
