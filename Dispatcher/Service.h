#pragma once
#pragma warning( disable: 4512 )
#include "local.h"

typedef void(*ThreadFunPtr)(void);
typedef boost::thread Thread;

#include <string>
using namespace std;

class ConfigReader;

/**
 * Class representing the Dispatcher service. On a windows platform this creates a Windows Service, on
 * a linux/unix platform a simple program that's being run
 */
class Service
{
public:

	/**
	 * Constructor
	 */
	Service( const char* serviceName, ConfigReader& cfg);

	/**
	 * Destructor
	 */
	~Service();

	/**
	 * Adds a thread to the dispatcher service
	 */
	void addThread( ThreadFunPtr f );

	/**
	 * Starts the service
	 */
	void Start();

	/**
	 * Stops the service
	 */
	void Stop();

	/**
	 * Called when this dispatcher was pinged by the daemon
	 */
	void pinged();

	/**
	 * Called when the dispatcher feels it was not pinged for some time
	 */
	void notPinged();


	/**
	 * Tries to register to the daemon
	 */
	bool registerToDaemon();

	int getPingCounter() const
	{
		return pingCounter;
	}

	/**
	 * Get the instance of the service
	 */
	static Service* getMe();

protected:
	/**
	 * Runs the service
	 */
	void Run();

	/**
	 * Sends the given string to the daemon. Returns the reply from the daemon.
	 */
	string sendToDaemon(const string&);

#ifdef WIN32
	/**
	 * Logs a windows event
	 */
	void LogWindowsEvent( WORD eventType, const char* eventText );

	/**
	 * Updates the status
	 */
	void UpdateStatus(DWORD status);
#endif


protected:
#ifdef WIN32
	/**
	 * The main entry point of the windows service
	 */
	static void WINAPI Main( DWORD, LPTSTR* );

	/**
	 * ControlHandler method
	 */
	static void WINAPI ControlHandler( DWORD control );

	/**
	 * Closes the application in case of an unrecoverable error
	 */
	void ErrorExit(const char* lastFunc);
#endif

#ifndef WIN32
	/**
	 * The termination signal handler in Unix/Linux
	 */
	static void TermSignalHandler( int );
#else
	static void AtExit();
#endif	

protected:

	// the ping counter. Always increased by the notPinged and always zeroed by the pinged. When the 
	// dispatcher senses that this is a too big value, will try to connect to the daemon again
	int pingCounter;

	// the instance of the service
	static Service* me;

	// the vector holding the threads
	vector<Thread*> _threads;

	// the name of the service
	string ServiceName;

	// the IP of the daemon as read from the configuration file
	string daemonIp;

	// the port of the daemon
	string daemonPort;

	// this is the IP the dispatcher will run on (read from the config file, verified its existence on the host itself)
	string dispIp;

	// the host key that will go to the daemon
	string dmnSitekey;

	// the run mode of the application, console, service, application
	string runMode;

	// whether we should put an icon on the sys-tray (windows only)
	string icon;

#ifdef WIN32

	SERVICE_STATUS_HANDLE	ServiceStatusHandle;
	SERVICE_STATUS			ServiceStatus;

#endif

};
