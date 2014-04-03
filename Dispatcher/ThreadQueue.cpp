#include "Dispatcher.h"
#include "ThreadQueue.h"

#undef MSEC_QUEUE_SLEEP_TIME
#define MSEC_QUEUE_SLEEP_TIME 10

void ThreadQueue()
{
	while(true)
	{
		SLEEP(10);
		//LOG("ThreadQueue(): Loop\n");
		SCOPEDLOCK(queueMutex);
		for ( STL_QUEUEDMESSAGE::iterator msg = queuedMessages.begin(); msg != queuedMessages.end(); msg++)
		{
			for ( STL_SUBSCRIPTIONINFO::iterator sub = subscriptions.begin(); sub != subscriptions.end(); sub++ )
			{	
				if( (*sub)->receives( (*msg)->subject ) )
				{
					LOG("ThreadQueue(): Queued message sent.\n");
					CI_RESPONSE response = (*sub)->ci->sendMessage( (*msg)->message );
					msg = queuedMessages.erase(msg);
				}
			}
		}
	}
}
