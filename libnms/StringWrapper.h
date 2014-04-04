#ifndef _STRING_WRAPPER_H_
#define _STRING_WRAPPER_H_

#include "DefaultSerializableObject.h"

#include <string>

/**
 * Wrapper class to allow serialization of String values.
 */
class String : public DefaultSerializableObject
{
public:

    /**
     * Constructs a new String object, sets the value to default false.
     */
    String();

    /**
     * Constructs a new String object, setting the value to the parameter.
     * @param _val - the new value of the float
     */
    String ( const char* _val );

    /**
     * Constructs a new String value from the given string.
     * @param _sval - the string
     */
    String ( const std::string& _val );

    /**
     * Destructor
     */
    ~String();

    /**
     * Default casting of the String to a String value
     */
    const char* c_str() const ;

    /**
     * Returns the type description of the String class.
     * @return the type description of the String class
     */
    virtual const std::string& type() const;

    /**
     * Returns a string representation of the String object
     */
    virtual const std::string toString() const;

};

#endif
