#pragma once

#include "apidef.h"
#include "parameter_not_found.h"

#include <string>

class Parameter;

/**
 * This class is responsible for encapsulating the messages that are sent through the network.
 * Messages contain:
 * 1. different kind and type parameters that are added by the specific add*** functions,
 *    or can be queried by the get*** functions. These parameters are uniquely identified by
 *    their name. Each parameter has also a type (such as Integer, Float, String, Bool ...) and
 *    a value (such as 1, 3.1415, "Hello World", true, ...)
 * 2. a time to live value, which is set automatically to IMMEDIATE for synchronously sent messages
 *    or a default of 24 hours for asynchornous messages, or a user set timeout. the TTL is being calculated
 * Because of the design of the system objects from this class can not be copied, nor assigned. If you need,
 * to pass messages between your methods, please use either references, either pointers.
 * Right now the following data types can be added to the messages:
 * 1. int - the traditional integer
 * 2. long - the traditional long
 * 3. bool - the traditional bool
 * 4. float - the traditional float
 * 5. std::string - the standard string
 * 6. const char* - a constant character string
-* 7. RAW data (for example the content of a file) - will be encoded into B64 and sent afterwards as string
-* 8. double - the standard double type
-* 9. char - a plain character
 * Beside of the standard add/get methods the Message class supports an indexed approach too, where you
 * retrieve each of the individuals parameters by speceifying the name of the parameter as and index
 * into the message and from this point you can work with the parameters, such as setting/retrieving
 * their values. For how this is done, please see the Parameter class's documentation.
 * A quick example:
 * Message m;
 *  m["TEST"] = 123;
 * will create a Message object and add a new parameter to it, called "TEST" with the value 123.
 */
class LIBNMS_API Message
{
public:

    // the default 24 hours Time To Live of a Message
    static const int TTL_24H = 1000 * 60 * 60 * 24;

public:

    /**
     * Creates a new Message with a default Time To Live set to 24 hours
     */
    Message();

    /**
     * Creates a new message with the specified Time to Live (in milliseconds)
     * @param ttl - time to live, the period for which this message is being kept in the system
     *              (if sent asynchronously) before being deleted by the Dispatcher.
     */
    Message ( int ttl );

    /**
     * Destructor.
     */
    virtual ~Message ( void );


    /*
     * Methods below add different values to the message
     */


    /**
     * Adds an integer to this message
     * @param name - is the name of the integer parameter
     * @param value - is the value of the integer parameter (a primitive int)
     */
    bool add ( const std::string& name, int value );

    /**
     * Adds a string parameter to this message
     * @param name - the name of the string parameter
     * @param value - the value of the string parameter
     */
    bool add ( const std::string& name, const char* value );

    /**
     * Adds a string parameter to this message
     * @param name - the name of the string parameter
     * @param value - the value of the string parameter
     */
    bool add ( const std::string& name, const string& value );

    /**
     * Adds a float parameter to the message
     * @param name - the name of the parameter
     * @param value - the value of the real parameter
     */
    bool add ( const std::string& name, float value );

    /**
     * Adds a long parameter to the message
     * @param name - the name of the parameter
     * @param value - the value of the real parameter
     */
    bool add ( const std::string& name, long value );

    /**
     * Adds a boolean value to this message
     * @param name - the name of the boolean parameter
     * @param value - true or false
     */
    bool add ( const std::string& name, bool value );

    /**
     * Adds a double value to this message
     * @param name - the name of the double parameter
     * @param value - the value
     */
    bool add ( const std::string& name, double value );

    /**
     * Adds a Parameter to the message. Actually you should not use this message unless you
     * want to create the parameters by hand.
     */
    bool addParameter ( Parameter* param );

    /**
     * Retrieves the parameter with the given name in case it exists. This has a read/write
     * access on the message, so with this you are actually creating the parameters. This
     * method is used in the phase where the message is just being constructed and you
     * specify the values for the
     * @param name - the name of the parameter to retrieve or create
     */
    Parameter& operator[] ( const std::string& name );


    /*
     * Methods below are used to retrieve values from the message
     */


    /**
     * Returns the string associated to stringName
     * If no string parameter exists with the given name empty string is returned.
     * This method does not throw.
     * @param stringName: the name of the string parameter
     * @return the value of the string parameter with the specified name.
     */
    string getString ( const std::string& stringName ) throw();

    /**
     * Returns the integer variable associated with the given name
     * if no parameter was defined for the given name 0 (zero) is returned.
     * This method does not throw.
     * @param intName: the name of the integer parameter
     * @return the value of the int parameter with the specified name
     */
    int getInt ( const std::string& intName ) throw();

    /**
     * Returns the real number variable associated to the given name
     * if no parameter was defined for the given name 0 (zero) is returned.
     * This method does not throw.
     * @param floatName: the name of the float parameter
     * @return the value of the float parameter with the specified name
     */
    float getFloat ( const std::string& floatName ) throw();

    /**
     * Returns the boolean value associated to the given name
     * if no parameter was defined for the given name false is returned
     * This method does not throw.
     * @param floatName: the name of the boolean parameter
     * @return the value of the boolean parameter with the specified name
     */
    bool getBool ( const std::string& boolName ) throw();

    /**
     * Returns the long value associated to the given name
     * if no parameter was defined for the given name 0 is returned
     * This method does not throw.
     * @param floatName: the name of the long parameter
     * @return the value of the long parameter with the specified name
     */
    long getLong ( const std::string& longName ) throw();

    /**
     * Returns the double value associated to the given name
     * if no parameter was defined for the given name 0 is returned
     * This method does not throw.
     * @param floatName: the name of the real number
     * @return the of the double parameter with the specified name
     */
    double getDouble ( const std::string& doubleName ) throw();

    /**
     * Retrieves a parameter (read-only access only). In case there is no parameter with the
     * requested name, this method will THROW an exception in form of a string. To spare some
     * construction time, catch it with a reference. This operator is being used in the
     * Receiver::receive method (actually YOUR derived class's receive method), where the parameter
     * is "const Message&" so there be prepared to catch this exception.
     * @param name - the name of the parameter
     */
    const Parameter& operator[] ( const std::string& name ) const throw ( parameter_not_found );

private:

    /*
     * Unimplemented copy constructor
     */
    Message ( const Message& other );

    /*
     * Unimplemented assignment operator
     */
    Message& operator = ( const Message& rhs );

};
