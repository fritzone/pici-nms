#ifndef _MESSAGEIMPL_H_
#define _MESSAGEIMPL_H_

#include <string>
#include <vector>

class Message;
class Parameter;

/**
 * This class is responsible for encapsulating the messages that are sent through the network.
 * Messages contain:
 * 1. different kind and type variables that are added by the specific add*** functions,
 * or can be queried by the get*** functions.
 * 2. a subject (you name it as address too) where the messages are sent.
 *
 * The logic of the variables is the following:
 * 1. Each variable has
 *   - a name (such as: TESTVARIABLE)
 *   - a type (such as String)
 *   - a value (such as "Hello world")
 * 2. The ultimate role of the Message class is to send all its variables through the network to the
 *    subject that is specified when the message object is sent using the Transporter class
 */
class MessageImpl
{
public:

    /**
     *  Creates a new Message
     */
    MessageImpl ( int _ttl );

    /**
     * Destroys a message, destroys all the variables
     */
    virtual ~MessageImpl ( void );

    /**
     * Serializes this object. The result is the XML of all the parameters of the message
     * @return the serialized string as XML
     */
    std::string serialize();

    /**
     * Returns the string value associated to the variable stringName
     * if no string variable was defined with the given name empty string is returned
     * @param stringName: the name of the string vatriable
     */
    std::string getString ( const std::string& stringName );

    /**
     * Returns the numeric variable associated with the given name
     * if no numeric variable was defined for the given name 0 (zero) is returned
     * @param intName: the name of the numeric variable
     */
    int getInt ( const std::string& intName );

    /**
     * Returns the real number variable associated to the given name
     * if no variable was defined for the given name 0 (zero) is returned
     * @param floatName: the name of the real number
     */
    float getFloat ( const std::string& floatName );

    /**
     * Returns the bool associated to the given name
     */
    bool getBool ( const std::string& boolName );

    /**
     * Returns the long associated to the given name
     */
    long getLong ( const std::string& longName );

    /**
     * Returns the double associated to the given name
     */
    double getDouble ( const std::string& doubleName );


    /**
     * Adds a parameter to this message implementation. The parameter is already set up with a name and a value.
     * This method is used by the Message class to pass in the parameters from the API user
     */
    void addParameter ( Parameter* data );

    /**
     * Retrieves the TTL of the message
     */
    long getTtl() const
    {
        return ttl;
    }

    /**
     * Retrieves the parameter with the given value
     */
    Parameter* getParameter ( const std::string& name );

public:

    /**
     * Deserializes the message from the given string. The format must be identical to the one
     * supplied by the serialize method.
     */
    static Message* deserialize ( const char* src );

private:

    // all the data of this class
    std::vector<Parameter*> parameters;

    // the subject to which this message will be sent
    std::string sendSubject;

    // the ID of the message (each message has a unique ID based on timestamp and an index)
    std::string messageId;

    // this counts the messages sent by an application
    static int messageCounter;

    // this can be or the subject, where it was sent, or the sync-requester's ID
    std::string dest;

    // the time to live of the message
    long ttl;

};

#endif
