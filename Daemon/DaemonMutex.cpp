#include <stdio.h>
#include <stdlib.h>
#include "DaemonMutex.h"

#ifdef __linux__
#include <pthread.h>
#include "Logger.h"
#endif

DaemonMutex::DaemonMutex()
{
    pthread_mutexattr_init ( &attr );
    pthread_mutex_init ( &Dmutex, &attr );
}

int DaemonMutex::lock()
{
    int waitResult = pthread_mutex_lock ( &Dmutex );
    if ( waitResult != 0 )
    {
        LOG ( "Wait Failed" );
    }
    return ( ( int ) waitResult );
}

int DaemonMutex::unlock()
{
    return pthread_mutex_unlock ( &Dmutex );
}
