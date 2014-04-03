#pragma once
#include "ClientInfo.h"

class SubscriptionInfo
{
public:
	SubscriptionInfo(std::string subj, ClientInfo* cinfo); // creates a new Subscription Info object
	~SubscriptionInfo();
	std::string subject;	/// the subject
	ClientInfo *ci;	/// the client, which is subscribed to this subject
	bool receives( std::string ); /// return true when this subscription info may get messages to the parm
};

