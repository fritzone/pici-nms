#include "ThreadDispatcher.h"
#include "ExceptionDispatcher.h"
#include "Service.h"
#include <boost/lexical_cast.hpp>

#include <string>

using namespace std;

#define RESERVE(x,y) x.reserve( y + 1)
#define ACKM(iClient,sCommand) c_format("%s#%d:ACK",sCommand,iClient)

void ThreadDispatcher()
{
	TCPACCEPTOR( NAME(Listener), IO, DISPATCHER_PORT );
	WHILE(true)
	{
		LOG("Waiting for a client\n");
		tcp::socket* s = new tcp::socket(IO);
		Listener.accept(*s);
		LOG("New client connected\n");
		TCPClient* sock = new TCPClient(s);
		LOG("Dispatching client\n");
		DO_DISPATCH(sock);
	}
}

void DO_DISPATCH(TCPClient* sock)
{
	int iBytes;
	int iMsgSz;
	std::string sMessage, sCommand;

	SCOPEDLOCK(dispatcherMutex);

	TRY
	{
		FS_COMM_1: //first step: receive the Message itselfs
		{
			LOG("Receiving something from the client\n");
			iBytes = sock->ReceiveBytes(sMessage);
			if ( iBytes == RECVERROR ) throw EXCEPTION( ExceptionDispatcherLostConnection );
			DEBUGSTR(sMessage);

			// this is coming actually from the daemon, to see if this dispatcher is here or not
			if(sMessage == COMMAND_DSP_PING)
			{
				sock->SendBytes("DSP_PONG");
				Service::getMe()->pinged();
				return;
			}
		}

		HANDLE_MSG:
		{
			if (!getto(sMessage,sCommand,"#") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
		}	

		if ( sCommand == COMMAND_HELLO ) DO_CMDHELLO(sock,sMessage);
		else if ( sCommand == COMMAND_SUBSCRIBE ) DO_CMDSUBSCRIBE(sock,sMessage);
		else if ( sCommand == COMMAND_UNSUBSCRIBE ) DO_CMDUNSUBSCRIBE(sock,sMessage);
		else if ( sCommand == COMMAND_MESSAGE ) DO_CMDMESSAGE(sock,sMessage);
		else throw EXCEPTION( ExceptionDispatcherUnknownCommand );
	}

	CATCH ( ExceptionRuntime& ex )
	{
		EXOUT(ex);
	}	
	CATCH (std::runtime_error& ex )
	{
		EXOUT(ex);
	}	

	CATCH ( ... )
	{
		LOG("%s:%d : unknown exception.\n",__FILE__,__LINE__);
	}

	LOG("Done with the dispatching of 1 client");
}



void DO_CMDHELLO( TCPClient* sock, std::string& sMessage ) //CMD HELLO: HELLO#clientNumber@IP:PORT
{
	LOG("DO_CMDHELLO( '%s' )\n", C_STR(sMessage) );
	int iBytes, iClient, iPort;
	std::string sCommand, sClientResponse, sClient, sIP, sPort;

	if (!extractto(sMessage,sCommand,"#") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	if (!extractto(sMessage,sClient,"@") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	if (!strtoi(sClient, iClient)) throw EXCEPTION( ExceptionDispatcherBadResponse ); // NOT A NUMBER
	if (!extractto(sMessage,sIP,":") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	ASSIGN(sPort,sMessage);
	if ( !strtoi(sPort,iPort) ) throw EXCEPTION( ExceptionDispatcherBadResponse ); // NOT A NUMBER
	ClientInfo* newClient = new ClientInfo(&IO,sIP,iPort,iClient);	
	clients.insert( std::pair<int,ClientInfo*>(iClient,newClient) );
	iBytes = sock->SendBytes(ACKM(iClient,COMMAND_HELLO));
	if ( iBytes == SENDERROR ) throw EXCEPTION( ExceptionDispatcherLostConnection );
}

void DO_CMDMESSAGE( TCPClient* sock, std::string& sMessage ) //7:HELLO.B:ASYNCH:<Message><Parameters></Parameters></Message>
{
	LOG("DO_CMDMESSAGE( '%s' )\n", C_STR(sMessage) );
	bool foundSubscription = false;
	std::string sCommand, sTemp, sClient, sSubject,  sMsgT, sMessageContent, sTTL;
	ASSIGN(sTemp,sMessage);
	if (!extractto(sTemp,sCommand,"#") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	if (!extractto(sTemp,sClient,":") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	if (!extractto(sTemp,sSubject,":") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	if (!extractto(sTemp,sMsgT,":") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	if (!extractto(sTemp,sTTL,":")) throw EXCEPTION( ExceptionDispatcherBadResponse );
	LOG("TTL:%s\n",sTTL.c_str());
	ASSIGN(sMessageContent,sTemp);
	long ttl = -1;
	try
	{
		ttl = boost::lexical_cast<long>(sTTL);
	}
	catch (boost::bad_lexical_cast& e)
	{
		LOG("Invalid TTL: %s\n", sTTL.c_str());
		throw EXCEPTION( ExceptionDispatcherBadResponse );
	}

	if(ttl < 0)
	{
		LOG("Invalid TTL: %s\n", sTTL.c_str());
		throw EXCEPTION( ExceptionDispatcherBadResponse );
	}

	// now since we are here, means that things were all right till now, send the message
	for ( STL_SUBSCRIPTIONINFO::iterator it = subscriptions.begin(); it != subscriptions.end(); it++)
	{
		if ( (*it)->receives(sSubject) )
		{
			foundSubscription = true;
			LOG("Sending a messge: ---[%s]---  to subj --[%s]--\n", sMessage.c_str(), sSubject.c_str());
			CI_RESPONSE response = (*it)->ci->sendMessage(sMessage);
		}
	}

	// now, add the message to the queue only if it was not sent, and the user specified that this message should
	// be kept in the system for some time for clients that will connect later
	if(!foundSubscription && ttl > 0)
	{
		LOG("Adding a new Queued message, since no subscription was found\n");
		SCOPEDLOCK(queueMutex);
		QueuedMessage *queuedMessage = new QueuedMessage(sSubject,sMessageContent, ttl);
		queuedMessages.push_back(queuedMessage);
	}
int iClient;
	if (!strtoi(sClient,iClient) ) throw EXCEPTION( ExceptionDispatcherBadResponse );
int iBytes = sock->SendBytes(ACKM(iClient,COMMAND_MESSAGE));
	if ( iBytes == SENDERROR ) throw EXCEPTION( ExceptionDispatcherLostConnection );

	LOG("DO_CMDMESSAGE is done\n");
}

void DO_CMDSUBSCRIBE( TCPClient* sock, std::string& sMessage ) //CMD SUBSCRIBE : HELLO#sClient:ACK 
{
	LOG("DO_CMDSUBSCRIBE( '%s' )\n", C_STR(sMessage) );
	int iBytes, iClient;
	std::string sCommand, sClient, sClientResponse, sSubject;
	if (!extractto(sMessage,sCommand,"#") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	if (!extractto(sMessage,sClient,":") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	if (!strtoi(sClient,iClient) ) throw EXCEPTION( ExceptionDispatcherBadResponse ); // NOT A NUMBER
	
	ASSIGN(sSubject,sMessage);
	
	STL_CLIENTINFO::iterator itClient = clients.find(iClient);
	if ( itClient == clients.end() ) throw EXCEPTION( ExceptionDispatcherNoClient );
	ClientInfo* pClient = (*itClient).second;
	SubscriptionInfo* sub = new SubscriptionInfo( sSubject, pClient );
	subscriptions.push_back(sub);
	if ( ( iBytes = sock->SendBytes(ACKM(iClient,COMMAND_SUBSCRIBE))) == SENDERROR ) throw EXCEPTION( ExceptionDispatcherLostConnection );
	
}


void DO_CMDUNSUBSCRIBE( TCPClient* sock, std::string& sMessage ) //CMD UNSUBSCRIBE  
{
	LOG("DO_CMDUNSUBSCRIBE( '%s' )\n", C_STR(sMessage) );

	int iBytes, iClient;
	std::string sCommand, sClient, sClientResponse, sSubject;

	if (!extractto(sMessage,sCommand,"#") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	if (!extractto(sMessage,sClient,":") ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	if (!strtoi(sClient,iClient) ) throw EXCEPTION( ExceptionDispatcherBadResponse );
	
	ASSIGN(sSubject,sMessage);
	
	for ( STL_SUBSCRIPTIONINFO::iterator it = subscriptions.begin(); it != subscriptions.end(); )
	{
		if( (*it)->subject == sSubject )
			if( (*it)->ci->clientNumber == iClient)
			{
				it = subscriptions.erase(it);
				continue;
			}
		it++;

	}

	if ( ( iBytes = sock->SendBytes(ACKM(iClient,COMMAND_UNSUBSCRIBE))) == SENDERROR ) throw EXCEPTION( ExceptionDispatcherLostConnection );

}

