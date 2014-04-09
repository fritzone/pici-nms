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

DaemonPingerThread::~DaemonPingerThread()
{

}

void* DaemonPingerThread::process()
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    while ( isAlive() )
    {
        if ( dmn == NULL )
        {
            fprintf ( stderr, "The Daemon is NULL\n" );
            return NULL;
        }

        const vector<RegisteredDispatcher*>& disps = dmn->getDispatchers();

        for ( size_t i = 0; i < disps.size(); i++ )
        {
            if ( !disps[i]->ping() )
            {
                dmn->removeDispatcher ( disps[i] );
            }
        }

        // TODO: Configurable ping time
#ifdef _WIN32
        Sleep ( 10000 );
#else
        sleep ( 10 );
#endif
    }
    return 0;
}
