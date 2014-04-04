#ifndef _DOUBLE_WRAPPER_H_
#define _DOUBLE_WRAPPER_H_

#include "DefaultSerializableObject.h"

#include <string>

/**
 * Wrapper class to allow serialization of doubleean (double) values. Also, provides methods for converting
 * doubleean values to string and vice-versa.
 */
class Double : public DefaultSerializableObject
{
public:

    /**
     * Constructs a new Double object, sets the value to default false.
     */
    Double();

    /**
     * Constructs a new Double object, setting the value to the parameter.
     * @param _val - the new value of the double
     */
    Double ( double _val );

    /**
     * Constructs a new Double value from the given string.
     * @param _sval - the string (either "true" or "false")
     */
    Double ( const std::string& _sval );

    /**
     * Destructor
     */
    ~Double();

    /**
     * Default casting of the Double to a double value
     */
    operator double () const ;

    /**
     * Returns the type description of the Double class.
     * @return the type description of the Double class
     */
    virtual const std::string& type() const;

    /**
     * Returns a string representation of the Double object
     */
    virtual const std::string toString() const;

};

#endif
