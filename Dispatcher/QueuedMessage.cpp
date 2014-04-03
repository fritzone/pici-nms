#include "QueuedMessage.h"

QueuedMessage::QueuedMessage( std::string _subject, std::string _message, long _ttl):subject(_subject), message(_message), ttl(_ttl)
{
	insertTime = time(NULL);
}
