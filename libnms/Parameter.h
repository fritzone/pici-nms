#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include "apidef.h"
#include "DefaultSerializableObject.h"
#include "invalid_type.h"
#include "parameter_not_found.h"

/**
 * This class represents a parameter that will be added to a message. The parameters have a name
 * and a value, and can be serialized to be able to be sent over the network and deserialized
 * so that we can restore the original value from data received from the network.
 */
class LIBNMS_API Parameter : public DefaultSerializableObject
{
public:

    /**
     * Builds a new Parameter object with the given name
     * @param name - the name of the parameter
     */
    Parameter ( const std::string& _name );

    /**
     * Creates a new parameter object with the given name and the given value
     * @param _name - the name of the object
     * @param _value - the value of the object
     */
    Parameter ( const std::string& _name, SerializableObject* _value );

    /**
     * Destructor
     */
    ~Parameter();

    /**
     * Returns the type of the data as a string that can be put into the XML without too much complication
     * @return the type of this class as a text
     */
    virtual const std::string& type() const ;

    /**
     * Returns the name of the parameter
     */
    const std::string& name() const;

    /**
     * Assigns an int value to this parameter
     * @param value - the int value this parameter will hold
     */
    Parameter& operator = ( int value );

    /**
     * Assigns a string to this parameter
     * @param value - the string value this parameter will hold
     */
    Parameter& operator = ( const char* value );

    /**
     * Assigns a bool to this parameter
     * @param value - the bool value
     */
    Parameter& operator = ( bool value );

    /**
     * Assigns a long value to this parameter
     * @param value - the long value this parameter will hold
     */
    Parameter& operator = ( long value );

    /**
     * Assigns a float value to this parameter
     * @param value - the float value this parameter will hold
     */
    Parameter& operator = ( float value );

    /**
     * Assigns a char value to this parameter
     * @param value - the char value this parameter will hold
     */
    Parameter& operator = ( char value );

    /**
     * Assigns a double value to this parameter
     * @param value - the double value this parameter will hold
     */
    Parameter& operator = ( double value );

    /**
     * Retrieve the value of the parameter if it holds an int. In case it doesn't hold an
     * integer it will throw an exception.
     */
    operator int () const throw ( invalid_type, parameter_not_found );

    /**
     * Retrieve the value of the parameter if it holds a long. In case it doesn't hold a
     * long value it will throw an exception.
     */
    operator long() const throw ( invalid_type, parameter_not_found );

    /**
     * Retrieve the value of the parameter if it holds a float. If the parameter does not hold a float
     * then the function call will throw an exception
     */
    operator float() const throw ( invalid_type, parameter_not_found );

    /**
     * Returns the value of the parameter in case it's holding a string like variable.
     * In case there's not string in the parameter it will throw an exception
     */
    operator const char* () const throw ( invalid_type, parameter_not_found );

    /**
     * Returns the value of this parameter as a boolean value (if it holds a bool)
     * or throws
     */
    operator bool() const throw ( invalid_type, parameter_not_found );

    /**
     * Returns the value of this parameter as a double value (if it holds a double)
     * or throws
     */
    operator double() const throw ( invalid_type, parameter_not_found );

    /**
     * Returns the value of this parameter as a char value (if it holds a char)
     * or throws
     */
    operator char() const throw ( invalid_type, parameter_not_found );

private:

    /*
     * Private copy constructor. Parameters should not be copied
     */
    Parameter ( const Parameter& other );

    /*
     * Assignment operator. Parameters should not be assigned
     */
    Parameter& operator = ( const Parameter& rhs );

};

#endif
