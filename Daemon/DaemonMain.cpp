#include "Daemon.h"
#include "Logger.h"

#ifdef _WIN32
#include "DaemonService.h"
#include <Windows.h>
#endif

#include <stdlib.h>
#include <unistd.h>

/**
 * This will be called when the daemon will exit
 */
void daemonExit()
{
    LOG ( "Daemon is being shut down... cleaning up the mess" );
}

/**
 * Main entry point
 */
#ifdef _WIN32
int WINAPI WinMain ( HINSTANCE, HINSTANCE, LPSTR cmdLine, int )
#else
int main()
#endif
{
    Logger::init ( ( char* ) "c:\\daemon.log" );
    LOG ( "Daemon starting" );
#ifdef _WIN32
    Service dmnServ;
    dmnServ.Start();
#else
    atexit ( daemonExit );
    Daemon dmn;
    if ( !dmn.startup() )
    {
        LOG ( "Could not start the application" );
        return 1;
    }

    while ( true )
    {
        sleep ( 1 );
    }
    return 0;

#endif
}

