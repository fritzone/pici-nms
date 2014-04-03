#include "local.h"
#include "Dispatcher.h"
#include "ThreadDispatcher.h"
#include "ThreadQueue.h"
#include "ThreadPinger.h"
#include "Service.h"
#include "ConfigReader.h"

#ifdef WIN32
#include "RegConfReader.h"
#endif

#include <string>

using namespace std;

#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/creation_tags.hpp>

LOGFILE( "c:\\dispatcher.log" );

boost::mutex dispatcherMutex; 
boost::mutex queueMutex;

boost::condition dispatcherPaused;
boost::condition QueueIsAvailable;
boost::asio::io_service IO;

using namespace boost::interprocess;

STL_QUEUEDMESSAGE queuedMessages; 
STL_CLIENTINFO clients;
STL_SUBSCRIPTIONINFO subscriptions;

#ifdef WIN32
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR cmdLine, int ) 
#else
int main()
#endif
{ 

#ifdef WIN32
	std::string confLocation = RegConfReader::getConfigFileLocation("Dispatcher");
	ConfigReader cfg ("dispatcher.xml", confLocation);
#else
	ConfigReader cfg ("dispatcher.xml");
#endif

	if(!cfg.configLoaded())
	{
		LOG("Cannot read configuration from the config file");
		return 1;
	}

std::string port = cfg.getValue("network", "socket", "port");

#ifndef WIN32
	port = "disp_" + port;
	try
	{
		boost::interprocess::named_mutex instmtx(open_or_create, port.c_str());	
		if(!instmtx.try_lock())
		{
			cerr << "On this host there's already running a dispatcher on "<< port << endl;
			return 1;
		}
	}
	catch(std::exception& e)
	{
		cerr << "Cannot create mutex. Reason:" << e.what() << endl;
	string sterr = cfg.getValue("run", "behavior", "startup-errors");
		if (sterr == "ignore")
		{
			cerr << "Due to config settings ignoring the error." << endl;
		}
		else
		{
			return 1;
		}
	}
#else
	port = "Global\\" + port;
HANDLE mtx = CreateMutex(NULL, 1, port.c_str());
	if(mtx == NULL)
	{
	DWORD lastErr = GetLastError();
		if(lastErr == ERROR_INVALID_HANDLE)
		{
			::MessageBox(NULL, "There is already a dispatcher running on this machine using the same configuration file", "Error", MB_OK);
			return 1;
		}
	}
	else
	{
	DWORD lastErr = GetLastError();
		if(lastErr == ERROR_ALREADY_EXISTS)
		{
			::MessageBox(NULL, "There is already a dispatcher running on this machine using the same configuration file", "Error", MB_OK);
			return 1;
		}
	}
#endif

Service	service("PICI-NMS Dispatcher", cfg); 
	service.addThread( ThreadDispatcher );
	service.addThread( ThreadPinger );
	service.addThread( ThreadQueue );
	service.Start(); 

	return 0; 
}
