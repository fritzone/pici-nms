#pragma once
#include "local.h"

class QueuedMessage
{
	public:
		QueuedMessage( std::string _subject, std::string _message, long _ttl); /// Creates a new object, the parameters: the subject and the message
		std::string subject; /// the subject, where this message was sent
		std::string message; /// the Message itself
	private:
		time_t insertTime;	/// the timestamp, when this message was added to the queue
		long ttl;			// the Time To Live of this message
};

