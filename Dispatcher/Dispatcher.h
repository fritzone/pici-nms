#pragma once

#include "local.h"
#include "QueuedMessage.h"
#include "SubscriptionInfo.h"
#include "util.h"

typedef VECTOR(QueuedMessage*) STL_QUEUEDMESSAGE;
typedef VECTOR(SubscriptionInfo*) STL_SUBSCRIPTIONINFO;
typedef MAP(int,ClientInfo*) STL_CLIENTINFO;

extern boost::asio::io_service IO;
extern boost::mutex dispatcherMutex; // the mutex handle to the dispatcher thread
extern boost::mutex queueMutex;// the mutex handle to the queue of queued messages
extern boost::condition QueueIsAvailable;
extern boost::condition dipatcherPaused;

extern STL_QUEUEDMESSAGE queuedMessages; /// this vector holds the queued messages
extern STL_CLIENTINFO clients;/// this vector holds the subscribed clients
extern STL_SUBSCRIPTIONINFO subscriptions;/// this vector holds the subscriptions

