#ifndef _PNMS_CLIENT_H_
#define _PNMS_CLIENT_H_

#include <string>

using namespace std;

/**
 * Basic class for PICI/NMS clients. Contains all the methods that are common for different kind of clients
 * such as subscribe/unsubscribe/send message... Clients (programmers) cannot instantiate an instance of
 * this class since it does not provide any mechanism to connect to the PICI/NMS network, these mechanisms
 * are implemented in underlying classes for Dynamic, Secure and Trusted clients.
 * To easily identify the clients in a programmer friendly way, there is the possibility to give each client
 * a name, and this mechanism is used in the direct client to client communication.
 */
class PnmsClient
{
public:

    PnmsClient ( string name );

    /**
     * Makes a new subscription for this client in the PICI/NMS network. After this call is being made the
     * receiver object will receive all the messages that have been sent to the given subject.
     * @param subject - the subject to which this client wants to subscribe
     * @param receiver - the receiver object which will get all the messages that are sent to the given subject
     */
    bool subscribe ( const string& subject, Receiver* receiver );

private:

    // the name of the client
    string name;
};

#endif
