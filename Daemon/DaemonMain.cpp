#include "Daemon.h"
#include "Logger.h"

#include "DaemonService.h"
#include <signal.h>
#include <boost/shared_ptr.hpp>

#include <stdlib.h>
#include <unistd.h>

boost::shared_ptr<Service> dmnService;

void on_sigint(int)
{
    signal(SIGINT, 0);
    dmnService->Stop();
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
    signal(SIGINT, on_sigint);
    Logger::init ( ( char* ) "pnms-daemon.log" );

    dmnService.reset(new Service());
    dmnService->Start();

    return 0;
}

