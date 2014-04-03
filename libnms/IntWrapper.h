#ifndef _INTEGER_WRAPPER_H_
#define _INTEGER_WRAPPER_H_

#include "Number.h"

/**
 * Class wrapper for the primitive int type. Objects of this class can be added to the messages
 * that will be sent over the wire to different clients that are subscribed to different subjects.
 */
class Integer : public Number
{
public:

	/**
	 * Default constructor, sets the value to 0
	 */
	Integer();

	/**
	 * Constructs an integer with the specified value
	 * @param _val - the value which this Integer object will contain
	 */
	Integer(int _val);

	/**
	 * Constructs an Integer from the given string representing an int value
	 * @param ser - a number as string
	 */
	Integer(const string& _sval);

	/**
	 * Destructor
	 */
	~Integer();

	/**
	 * Default casting of the Integer to an int value
	 */
	operator int () const ;

	/**
	 * Returns the type description of the Integer class. 
	 * @return the type description of the Integer class
	 */
	virtual const string& type() const;

	/**
	 * Returns a string representation of the given number
	 */
	virtual const string toString() const;

};

#endif
