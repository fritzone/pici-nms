#ifndef _DAEMON_SERVICE_H_
#define _DAEMON_SERVICE_H_

#ifdef _WIN32
#include <Windows.h>
#endif

#include <string>
#include <boost/shared_ptr.hpp>

using namespace std;

class Daemon;

/**
 * Class representing the daemon service if run from _Win32 as a service
 */
class Service
{
public:

    /**
     * Constructor
     */
    Service ( const char* serviceName = "PICI-NMS Daemon" );

    virtual ~Service();

    /**
     * Starts the service
     */
    void Start();

    /**
     * Stops the service
     */
    void Stop();

protected:

    /**
     * Runs the service
     */
    void Run();

protected:

    // the instance
    static Service* me;

    // the service name
    std::string ServiceName;

private:

    // the actual daemon
    boost::shared_ptr<Daemon> dmn;

#ifdef _WIN32
    SERVICE_STATUS_HANDLE   ServiceStatusHandle;
    SERVICE_STATUS          ServiceStatus;
    static void WINAPI Main ( DWORD, LPTSTR* );
    static void WINAPI ControlHandler ( DWORD control );
    void LogWindowsEvent ( WORD eventType, const char* eventText );
    void UpdateStatus ( DWORD status );
#endif

};

#endif
