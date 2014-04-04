#ifndef _CHAR_WRAPPER_H_
#define _CHAR_WRAPPER_H_

#include "DefaultSerializableObject.h"

/**
 * Wrapper class to allow serialization of charean (char) values. Also, provides methods for converting
 * charean values to string and vice-versa.
 */
class Char : public DefaultSerializableObject
{
public:

    /**
     * Constructs a new Char object, sets the value to default false.
     */
    Char();

    /**
     * Constructs a new Char object, setting the value to the parameter.
     * @param _val - the new value of the char
     */
    Char ( char _val );

    /**
     * Constructs a new Char value from the given string.
     * @param _sval - the string (either "true" or "false")
     */
    Char ( const string& _sval );

    /**
     * Destructor
     */
    ~Char();

    /**
     * Default casting of the Char to a char value
     */
    operator char () const ;

    /**
     * Returns the type description of the Char class.
     * @return the type description of the Char class
     */
    virtual const string& type() const;

    /**
     * Returns a string representation of the Char object
     */
    virtual const string toString() const;

};

#endif
