#include "RegisteredDispatcher.h"
#include "NetworkAddress.h"
#include "TcpSocket.h"

#include <stdlib.h>
#include <unistd.h>

RegisteredDispatcher::RegisteredDispatcher(const string& strip, const string& strport, const string& ssitekey) : addr(strip), port(-1), sitekey(ssitekey)
{
	port = atoi(strport.c_str());
}

bool RegisteredDispatcher::ping()
{
NetworkAddress na(getIp(), port);
TCPSocket toDisp;
	toDisp.connectTo(&na);
	if(!toDisp.send("DSP_PING"))
	{
		return false;
	}
	#ifdef WIN32
	Sleep(100);
	#else
	sleep(1);
	#endif
	
string dspPong = toDisp.receive();
	if(dspPong != "DSP_PONG")
	{
		return false;
	}
	toDisp.close();
	return true;
}