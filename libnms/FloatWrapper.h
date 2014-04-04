#ifndef _FLOAT_WRAPPER_H_
#define _FLOAT_WRAPPER_H_

#include "Number.h"

#include <string>

/**
 * Wrapper class to allow serialization of float values. Also, provides methods for converting
 * floats to string and vice-versa.
 */
class Float : public Number
{
public:

    /**
     * Constructs a new Float object, sets the value to default 0.
     */
    Float();

    /**
     * Constructs a new Float object, setting the value to the parameter.
     * @param _val - the new value of the float
     */
    Float ( float _val );

    /**
     * Constructs a new Float value from the given string.
     * @param _sval - the string
     */
    Float ( const std::string& _sval );

    /**
     * Destructor
     */
    ~Float();

    /**
     * Default casting of the Integer to an int value
     */
    operator float () const ;

    /**
     * Returns the type description of the Float class.
     * @return the type description of the Float class
     */
    virtual const std::string& type() const;

    /**
     * Returns a string representation of the given number
     */
    virtual const std::string toString() const;

};

#endif
