#pragma once

class Message;

/**
 * This class represents the abstract entity, that will receive a message when
 * one is transmitted to a specified subject. You have to derive a class
 * from this, implement the receive method, create an instance of that class, and using the
 * subscribe method from the Transporter class subscribe the object to a message of your choice.
 */
class Receiver
{
public:

    virtual ~Receiver() {}

	/**
	 * This method is called when a message was received that was sent to the subject the instances of this
	 * class are subscribed to.
	 * @param message - is the message that actually is sent to the instance of this class by the client on the
	 * other end of the wire
	 */
	virtual void receive(const Message& msg) = 0;

};


