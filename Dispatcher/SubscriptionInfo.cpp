#include "SubscriptionInfo.h"

SubscriptionInfo::SubscriptionInfo(std::string subj, ClientInfo* cinfo) : subject(subj), ci(cinfo)
{

}

bool SubscriptionInfo::receives( std::string subj )
{
	size_t pos = subject.find(subj);
	LOG("SUBSCRIPTIONINFO::RECEIVES() => SUBJECT('%s'), SUBJ('%s'), NPOS(%d), POS(%d)\n",C_STR(subject),C_STR(subj),NPOS,pos );
	if ( pos == NPOS ) return false;
	return true;
}

SubscriptionInfo::~SubscriptionInfo()
{
	LOG("~SubscriptionInfo()\n");
}
