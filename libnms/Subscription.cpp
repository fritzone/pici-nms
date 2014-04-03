#include "Subscription.h"
#include "Receiver.h"

/**
 * Creates a new subscription object
 **/
Subscription::Subscription(string subj, Receiver* receiver)
{
	subject = subj;
	theReceiver = receiver;
size_t i = 0;
string subjField;
	while(i<subject.length())
	{
		subjField = "";
		while (subject[i] != '.' && i<subject.length()) 
		{
			subjField += subj[i++];
		}
		fields.push_back(subjField);
		i++;
	}
}

/**
 * This returns whether a Subscription object should receive
 * messages sent to subj.
 * The following cases should be handled:
 * X.Y.* this means the rest of the subjects after X.Y. More fields may come
 **/
bool Subscription::receives(string subj)
{
size_t i = 0;
size_t subjFieldVectorCounter = 0;
string subjField;
bool canAcc = true;

	while (i<subj.length()) 
	{
		subjField = "";
		while(subj[i] != '.' && i<subj.length())
		{
			subjField += subj[i++];
		}
		
		if(fields[subjFieldVectorCounter] != "*" && fields[subjFieldVectorCounter] != "*")
		{
			if(fields[subjFieldVectorCounter] != subjField)
			{
				canAcc = false;
				break;
			}
		}
		else
		{
			if(fields[subjFieldVectorCounter] == "*")
			{
				break;
			}
			else
			{
				i++;
				while (i < subj.length()) 
				{
					if(subj[i] == '.')
					{
						canAcc = false;
						break;
					}
					i++;
				}
				break;
			}
		}

		i++;
		subjFieldVectorCounter ++;
	}
	return canAcc;
}
