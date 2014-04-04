#pragma once

#include <vector>
#include <string>

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
    Subscription ( const std::string&, Receiver* );

    /// the subject
    std::string subject;

    /// The receiver, that is subscribed
    Receiver* theReceiver;

    /// return true when this object must receive the given message
    bool receives ( std::string );

private:
    /// message field mechanism
    std::vector<std::string> fields;

};
