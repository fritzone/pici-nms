#include <stdio.h>
#include <stdlib.h>
#include "Mutex.h"

#include <pthread.h>
#include "Logger.h"

Mutex::Mutex()
{
    pthread_mutexattr_init ( &attr );
    pthread_mutex_init ( &Dmutex, &attr );
}

int Mutex::lock()
{
    int waitResult = pthread_mutex_lock ( &Dmutex );
    if ( waitResult != 0 )
    {
        LOG ( "Wait Failed" );
    }
    return ( ( int ) waitResult );
}

int Mutex::unlock()
{
    return pthread_mutex_unlock ( &Dmutex );
}
