#ifndef _PNMS_GENERIC_CLIENT_IMPL_H_
#define _PNMS_GENERIC_CLIENT_IMPL_H_

#include <string>

using namespace std;

class Transporter;
class ClientIdentity;
class Receiver;
class Message;

/**
 * Generic implementation of a Pnms client, used directly by the Dynamic and Secure clients
 */
class PnmsGenericClientImpl
{
public:

	/**
	 * Default constructor
	 */
	PnmsGenericClientImpl();

	/**
	 * Destructor
	 */
	~PnmsGenericClientImpl();

	/**
	 * Constructor. Creates a new instance of a client. Based on the clientType parameter the constructor
	 * decides whether it's a dynamic client or a secure client.
	 */
	PnmsGenericClientImpl(const string& name, int clientType);

	/**
	 * Returns the transporter object of the client.
	 */
	Transporter* getTransporter() const;

	/**
	 * Returns the identity of the client
	 */
	const ClientIdentity* getIdentity() const;

	/**
	 * Returns the initialization state of the object
	 * @return true if this object is successfully initialized, false if not...
	 */
	bool isInitialized() const;

	/**
	 * Executes the given subscription call, and the instance of the Receiver (abstract) class
	 * will receive all the messages that are sent with the subject subject
	 * @param subject: The subject to which the receiver will subscribe
	 * @param theReceiver: The receiver that will subscribe to the subject
	 * @return false in case of a failure
	 */
	bool subscribe(const string& subject, Receiver* receiver);

	/**
	 * Unsubscribes from the given subject
	 * @param subject: The subject from which the receiver will unsubscribe
	 * @return false in case of a failure
	 */
	bool unsubscribe(const string& subject);

	/**
	 * Publishes the given message to the PICI-NMS network for other clients that are subscribed
	 * to the subject. The dispatcher is responsible from this moment to handle the Time To Live (TTL)
	 * of the message and deliver it to clients when the message has expired. The dispatcher implementation
	 * can decide whether to keep the message in a database or somewhere else. The message will be deleted from
	 * the dispatcher internals when it has expired.
	 * @param subject: The subject to where to send the message
	 * @param msg: The message that will be sent
	 * @return false in case of a failure
	 */
	bool publishMessage(const string& subject, const Message& msg);

protected:

	// the identity of the client. It's a const object so that we can't modify it by accident.
	const ClientIdentity* identity;

	// this object is used to communicate with the PNMS network
	Transporter* transporter;

	// the name of the client, as used in synchronous communication
	string name;

};

#endif
