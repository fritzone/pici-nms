#pragma once

#include <string>

using namespace std;

class Message;
class Receiver;
class TransporterImpl;
class ClientIdentity;
class AbstractClientInitializer;

/*
 * The following connection modes identify the method a client will use to connect to the
 * PICI-NMS network.
 */

extern int DYNAMIC_CLIENT;

/**
 * Secure clients read the client side configuration of the PICI NMS network from a configuration file
 * and connect using TCP sockets to the Daemon found in the config file. These clients can connect to
 * the Daemon under every circumstance if the Daemon is Up and Running
 * These clients can send encrypted messages, but these messages are not authenticated by the network.
 * It is the responsibility of the user of the API (ie. the programmer, YOU) to manually encrypt and
 * decrypt the messages using the provided APIs, and to transfer the encryption key between clients.
 * Secure clients can send messages to dynamic clients, but cannot send message to authenticated clients.
 */
extern int SECURE_CLIENT;

/**
 * Trusted clients connect to the PICI-NMS network and authenticate using credentials provided by the
 * user of the API. Trusted clients always send authenticated messages which are automatically encrypted
 * and decrypted by the underlying API, and are automatically authenticated by the PICI-NMS network
 * on receipt and delivery. The authentication of a trusted client is done by the daemon when the client
 * is requesting it ClientID. The daemon matches the user/password sent by the client to the user/password
 * pair that was entered in the system by the PICI/NMS network administrator. This user/password pair
 * IS NOT YOUR LOGIN NAME/PASSWORD!!!
 */
extern int TRUSTED_CLIENT;

/**
 * Class responsible for transmitting messages through the network. The primary role of this class
 * is to make subscriptions of different local objects to different messages and to deliver messages
 * that are sent between these objects.
 */
class Transporter
{
public:

    /**
     * Creates a new object. Performs basic initialization stuff, such as establishing a connection
     * to the network, creating a local TCP server for accepting incoming messages, etc...
     */
    Transporter ( int authenticationMethod );

    /**
     * Initializes the transporter using the given initializer object
     * @param initializer - the initializer of the transporter
     */
    Transporter ( AbstractClientInitializer* initializer );

    /**
     * Destroys an existing object and frees all its resources. Also closes the connections, terminates
     * the local TCP server.
     */
    ~Transporter ( void );

    /**
     * Returns the initialization state of the object
     * @return true if this object is successfully initialized, false if not...
     */
    bool isInitialized();

    /**
     * Executes the given subscription call, and the instance of the Receiver (abstract) class
     * will receive all the messages that are sent with the subject subject
     * @param subject: The subject to which the receiver will subscribe
     * @param theReceiver: The receiver that will subscribe to the subject
     * @return false in case of a failure
     */
    bool subscribe ( const string& subject, Receiver* theReceiver );

    /**
     * Unsubscribes from the given subject
     * @param subject: The subject from which the receiver will unsubscribe
     * @return false in case of a failure
     */
    bool unsubscribe ( const string& subject );

    /**
     * Sends the given message to the given subject.
     * @param subject: The subject to where to send the message
     * @param msg: The message that will be sent
     * @return false in case of a failure
     */
    bool sendMessage ( const string& subject, const Message& msg );

    /**
     * Sends the Message to the given subject, and waits for an answer to come back from the
     * receiver which is subscribed. Only one receiver should be subscribed to one message.
     * @param subject: is the subject to which the message is sent
     * @param msg: is the message that actually is sent
     * @param timeout: is the time in seconds that we wait for the response to arrive. If you specify
     *                 zero we don't wait for the answer to come, specify quite a big value if you need...
     * @return the response that was sent by the receiver which was subscribed to the 'subject'. The caller is
     * responsible for deleting this object.
     */
    Message* sendAndWaitAnswer ( const string& subject, Message* msg, int timeout );

    /**
     * Returns the identity of the client
     */
    const ClientIdentity* getIdentity();

};
