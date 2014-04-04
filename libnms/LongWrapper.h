#ifndef _LONG_WRAPPER_H_
#define _LONG_WRAPPER_H_

#include "Number.h"

#include <string>

/**
 * Wrapper class to allow serialization of Long values. Also, provides methods for converting
 * Longs to string and vice-versa.
 */
class Long : public Number
{
public:

    /**
     * Constructs a new Long object, sets the value to default 0.
     */
    Long();

    /**
     * Constructs a new Long object, setting the value to the parameter.
     * @param _val - the new value of the Long
     */
    Long ( long _val );

    /**
     * Constructs a new Long value from the given string.
     * @param _sval - the string
     */
    Long ( const std::string& _sval );

    /**
     * Destructor
     */
    ~Long();

    /**
     * Default casting of the Integer to an int value
     */
    operator long () const ;

    /**
     * Returns the type description of the Long class.
     * @return the type description of the Long class
     */
    virtual const std::string& type() const;

    /**
     * Returns a string representation of the given number
     */
    virtual const std::string toString() const;

};

#endif
