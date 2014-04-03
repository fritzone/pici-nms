#ifndef _TRANSPORTER_IMPL_H_
#define _TRANSPORTER_IMPL_H_

#include <string>
#include <vector>

using namespace std;

class Subscription;
class Receiver;
class Message;
class PnmsUDPSocket;
class NetworkAddress;
class CommandInterface;
class ThreadedTCPServer;
class TcpThread;
class LocalTCPClientFactory;
class ClientAcceptor;
class AbstractClientInitializer;
class ClientIdentity;

/// Dummy variable for a reference used in sendToDispatcher method of class TransporterImpl
static char* dummy = NULL;


/**
 * Class responsible for transmitting messages through the network. The primary role of this class
 * is to make subscriptions of different local objects to different messages and to deliver messages
 * that are sent between these objects.
 */
class TransporterImpl
{

	friend class TcpThread;
	friend class ConnectionThread;

public:


	/**
	 * Creates a new object. Performs basic initialization stuff, such as establishing a connection
	 * to the network, creating a local TCP server for accepting incoming messages, etc...
	 */
	TransporterImpl(int method);

	/**
	 * Creates a new object, uses the provided initializer to initialize the transporter
	 */
	TransporterImpl(AbstractClientInitializer* initer);

	/**
	 * Destroys an existing transporter object and frees all its resources. Also closes the connections, terminates
	 * the local TCP server.
	 */
	virtual ~TransporterImpl(void);
	
	/**
	 * Returns the initialization state of the object
	 * @return true if this object is is succesfully initialized, false if not...
	 */
	bool isInitialized();

	/**
	 * Executes the given subscription call, and the instance of the Receiver (abstract) class
	 * will receive all the messages that are sent with the subject subject
	 * @param subject: The subject to which the receiver will subscribe
	 * @param theReceiver: The receiver that will subscribeto the subject
	 */
	bool subscribe(const string& subject, Receiver* theReceiver);

	/**
	 * Sends the given message to the given subject.
	 * @param subject: The subject to where to send the message
	 * @param msg: The message that will be sent
	 */
	bool sendMessage(const string& subject, const Message& msg);

	/**
	 * Sends the Message to the given subject, and waits for an answer to come back from the 
	 * receiver which is subscribed. Only one receiver should be subscribed to one message.
	 * @param subject: is the subject to which the message is sent
	 * @param msg: is the message that actually is sent
	 * @param timeout: is the time in seconds that we wait for the response to arrive. If you specify 
	 *                 zero we don't wait for the answer to come, specify quite a big value if you need...
	 */
	Message* sendAndWaitAnswer(string subject, Message* msg, int timeout);

	/**
	 * Returns the client identity for those who might need it
	 */
	ClientIdentity* getClientIdentity();

	/**
	 * Returns the initializer of the transporter
	 */
	AbstractClientInitializer* getInitializer() const
	{
		return initializer;
	}

	/**
	 * Unsubscribes from the given subject
	 */
	bool unsubscribe(const string&);

	/**
	 * Checks whether this transporter implementation is subscriebd or not to this subject
	 */
	bool isSubscribed(const string&);

private:

	/**
	 * Initializes the secure client
	 */
	bool initSecureClient();

	/**
	 * This method handles the objects messages, i.e. it sends them to the proper Receiver object
	 */	
	void handleMessage(const string&, const Message&);
	
	/**
	 * Sends the "HELLO" message to the dispatcher (dynamic clients only)
	 */
	bool sendHelloToDispatcher();

	/**
	 * Executes some local initialization. Called from the constructor
	 */
	bool localInit();

private:


	// the address of the dispatcher, populated based on data received from the daemon
	NetworkAddress* dispatcherAddress;

	// the subscriptions in this transporter object
	vector<Subscription*> subscriptions;

	// the port, on which this objects TCP server is running
	int freePort;

	// the TCP Server's runner thread
	TcpThread* tcpThread;

	// the TCP Server object
	ThreadedTCPServer* localTcpServer;

	// this is the local Server's client factory that will be activated when the dispatcher decides to contact the local server
	LocalTCPClientFactory* tcpcf;

	// the client acceptor of the local server
	ClientAcceptor* ca;

	// the initializer of the transporter
	AbstractClientInitializer* initializer;

	// the identity of the client
	ClientIdentity* identity;
};

#endif
