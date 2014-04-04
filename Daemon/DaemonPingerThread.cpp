#include "DaemonPingerThread.h"
#include "RegisteredDispatcher.h"
#include "Daemon.h"

#include <vector>
#include <stdio.h>
#include <unistd.h>

using namespace std;

DaemonPingerThread::DaemonPingerThread ( Daemon* _dmn ) : Thread(), dmn ( _dmn )
{
}

void* DaemonPingerThread::process()
{
    printf ( "Starting the pringer thread\n" );
    printf ( "Not really..." );
    while ( true )
    {
        printf ( "Before a ping session" );
        if ( dmn == NULL )
        {
            printf ( "The Daemon is NULL" );
        }

        const vector<RegisteredDispatcher*>& disps = dmn->getDispatchers();

        for ( size_t i = 0; i < disps.size(); i++ )
        {
            printf ( "Pinging daemon #%i\n", i );
            if ( !disps[i]->ping() )
            {
                dmn->removeDispatcher ( disps[i] );
            }
        }
#ifdef _WIN32
        Sleep ( 10000 );
#else
        sleep ( 10 );
#endif
    }
    printf ( "Pringer thread leaving\n" );
    return NULL;
}
