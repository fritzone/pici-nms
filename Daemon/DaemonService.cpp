#include "Logger.h"
#include "DaemonService.h"
#include "Daemon.h"

#include "DaemonInnerTCPServerThread.h"
#include "DaemonUDPServerThread.h"
#include "DaemonPingerThread.h"

#include <stdlib.h>
#include <signal.h>

Service* Service::me = NULL;

#define C_CHAR(x) &x[0]
#define C_STR(x) x.c_str()

Service::Service ( const char* serviceName ) :  ServiceName ( serviceName )
{
    LOG ( "Service::Service()\n" );
    me = this;
#ifdef _WIN32
    ServiceStatusHandle = 0;
    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;
#endif

}

void Service::Run()
{
    dmn = new ( std::nothrow ) Daemon();
    if ( NULL == dmn )
    {
        LOG ( "Not enough memory" );
        exit ( 1 );
    }

    if ( !dmn->startup() )
    {
        LOG ( "Cannot start the daemon" );
        delete dmn;
        exit ( 1 );
    }

    dmn->daemonInnerThread->waitToFinish();
    dmn->dups->waitToFinish();
    dmn->pinger->waitToFinish();
}

void Service::Stop()
{

}

#ifdef _WIN32
void Service::Start()
{
    LOG ( "Service::Start()\n" );
    static SERVICE_TABLE_ENTRY ServiceTable[] = { { C_CHAR ( me->ServiceName ), Main }, { 0 , 0 } };
    if ( !StartServiceCtrlDispatcher ( ServiceTable ) )
    {
        me->LogWindowsEvent ( EVENTLOG_ERROR_TYPE, "Could not start service control dispatcher" );
        me->Stop();
    }
}
void WINAPI Service::Main ( DWORD, LPTSTR* )
{
    LOG ( "Service::Main()\n" );
    me->ServiceStatusHandle = RegisterServiceCtrlHandler ( C_STR ( me->ServiceName ), ControlHandler );
    if ( !me->ServiceStatusHandle )
    {
        me->LogWindowsEvent ( EVENTLOG_ERROR_TYPE,  "Could not register service control handler" );
    }
    me->UpdateStatus ( SERVICE_RUNNING );
    me->Run();
    me->UpdateStatus ( SERVICE_STOPPED );
}
void Service::LogWindowsEvent ( WORD eventType, const char* eventText )
{
    LOG ( "Service::LogWindowsEvent()" );
    HANDLE eventSource;
    eventSource = RegisterEventSource ( 0, C_STR ( ServiceName ) );
    if ( eventSource )
    {
        ReportEvent ( eventSource, eventType, 0, 0, 0, 1, 0, &eventText, 0 );
        DeregisterEventSource ( eventSource );
    }
}
void Service::UpdateStatus ( DWORD status )
{
    if ( ServiceStatusHandle )
    {
        ServiceStatus.dwCurrentState = status;
        SetServiceStatus ( ServiceStatusHandle, &ServiceStatus );
    }
}
void WINAPI Service::ControlHandler ( DWORD control )
{
    LOG ( "Service::ControlHandler()" );
    if ( control == SERVICE_CONTROL_STOP )
    {
        me->UpdateStatus ( SERVICE_STOP_PENDING );
        me->Stop();
        me->UpdateStatus ( SERVICE_STOPPED );
    }
}
#else
void Service::TermSignalHandler ( int )
{
    LOG ( "Service::TermSignalHandler()\n" );
    me->Stop();
    exit ( 0 );
}
void Service::Start()
{
    LOG ( "Service::Start()\n" );
    signal ( SIGTERM, TermSignalHandler );
    me->Run();
}
#endif

