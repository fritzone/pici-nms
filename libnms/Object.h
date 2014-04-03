#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>

using namespace std;

/**
 * Base class for all objects that can be added to a message.
 */
class Object
{
public:

	/**
	 * Constructor
	 */
	Object()
	{
	}

	/**
	 * Destructor
	 */
	virtual ~Object()
	{
	}

	/**
	 * Returns a unique MD5 hash-code for this object
	 */
	virtual string getHashCode() = 0;

	/**
	 * Returns the type of the data as a string that can be put into the XML without too much complication
	 */
	virtual const string& type() const = 0;
};

#endif
