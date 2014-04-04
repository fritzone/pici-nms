#pragma once

#include <vector>
#include <string>

using namespace std;

class Receiver;

/**
 * This class represents a subscription.
 * The two data members are:
 * The subject, to which the given receiver is subscribed
 */
class Subscription
{
public:
    // creates a new subscription class
    Subscription ( string, Receiver* );

    /// the subject
    string subject;

    /// The receiver, that is subscribed
    Receiver* theReceiver;

    /// return true when this object must receive the given message
    bool receives ( string );

private:
    /// message field mechanism
    vector<string> fields;

};