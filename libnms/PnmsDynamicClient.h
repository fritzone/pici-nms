#ifndef _PNMS_DYNAMIC_CLIENT_H_
#define _PNMS_DYNAMIC_CLIENT_H_

#include "apidef.h"

#include <string>

using namespace std;

class Message;
class Receiver;

/**
 * This class is an abstractization of a dynamic client.
 * Dynamic clients automatically discover the settings of the network by sending a UDP broadcast
 * message to be picked up by the Daemon's UDP server. These clients don't require a configuration
 * file to run, but on some networks there is a chance that the UDP server will not be discovered.
 * These clients cannot send encrypted messages since the authentication method makes it impossible.
 * Dynamic clients can send messages to secure clients, but cannot send messages to trusted clients.
 * This class cannot be copied nor assigned.
 */
class LIBNMS_API PnmsDynamicClient
{
public:

    /**
     * Constructor. Creates a new instance of a dynamic client. Settings of the PICI/NMS network will
     * be discovered automatically.
     * @param name - the logical name of the client, as known to the application programmer
     */
    PnmsDynamicClient ( const string& name );

    /**
     * Destructor
     */
    ~PnmsDynamicClient();

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
    bool subscribe ( const string& subject, Receiver* receiver );

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
    bool publishMessage ( const string& subject, const Message& msg );

private:

    /*
     * Copy constructor. Since this object is never supposed to be copied the Copy constructor
     * is private and is never implemented.
     */
    PnmsDynamicClient ( const PnmsDynamicClient& other );

    /*
     * The assignment operator. Since this class is not supposed to be assigned to this is private
     * and unimplemented.
     */
    PnmsDynamicClient& operator = ( const PnmsDynamicClient& rhs );
};

#endif

