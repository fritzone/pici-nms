#ifndef _PNMS_SECURE_CLIENT_H_
#define _PNMS_SECURE_CLIENT_H_

#include "apidef.h"

#include <string>

using namespace std;

class Message;
class Receiver;

/**
 * This class is an abstractization of a Secure client.
 * Secure clients require a configuration file to run, the location of the file should be either:
 *  - the directory where the application resides
 *  - the home directory of the user
 *  - passed in as a parameter to the client
 * These clients cannot send encrypted messages since the lack of authentication method makes it impossible.
 * Secure clients can send messages to secure clients and dynamic clients, but cannot send messages to trusted clients.
 * The client settings are always stored in a file named "client.xml".
 * This class can never be copied nor assigned.
 */
class LIBNMS_API PnmsSecureClient
{
public:

    /**
     * Constructor. Creates a new instance of a secure client. Settings of the PICI/NMS network will
     * be loaded from the configuration file stored in the location mentioned above.
     * @param name - the name of the client as known to the application developer using it
     */
    PnmsSecureClient ( const string& name );

    /**
     * Destructor
     */
    ~PnmsSecureClient();

    /**
     * Constructor. Creates a new instance of a secure client. Settings of the PICI/NMS network will
     * be loaded from the configuration file found in the directory specified in the parameter.
     * @param name - the name of the client as known to the application developer using it
     * @param configFileLocation - the configuration file holding the settings of the Pici NMS network.
     */
    PnmsSecureClient ( const string& name, const string& configFileLocation );

    /**
     * Returns the initialization state of the object
     * @return true if this object is successfully initialized, false if not...
     */
    bool isInitialized() const;

    /**
     * Executes the given subscription call, and the instance of the Receiver class
     * will receive all the messages that are sent with the subject subject
     * @param subject - The subject to which the receiver will subscribe
     * @param theReceiver - The receiver that will subscribe to the subject
     * @return false in case of a failure
     */
    bool subscribe ( const string& subject, Receiver* receiver );

    /**
     * Publishes the given message to the PICI-NMS network for other clients that are subscribed
     * to the subject. The dispatcher is responsible from this moment to handle the Time To Live (TTL)
     * of the message and deliver it to clients subscribing to the message till the message has expired.
     * The dispatcher implementation can decide whether to keep the message in a database or somewhere else.
     * The message will be deleted from the dispatcher internals (databse maybe) when it has expired.
     * @param subject - The subject to where to send the message
     * @param msg - The message that will be sent
     * @return false in case of a failure
     */
    bool publishMessage ( const string& subject, const Message& msg );

private:

    /*
     * Private and unimplemented
     */
    PnmsSecureClient ( const PnmsSecureClient& other );

    /*
     * Unimplemented assignment operator
     */
    PnmsSecureClient& operator = ( const PnmsSecureClient& rhs );
};

#endif

