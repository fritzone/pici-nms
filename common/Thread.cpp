#include "Logger.h"
#include "constants.h"

#include "Thread.h"

#include <memory.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
#ifndef CYGWIN
#include <Windows.h>
#endif
#endif

/**
 * Constructor
 */
Thread::Thread() : handle ( NULL ), threadAttrs ( NULL ), tid ( 0 ), started ( false ), alive(false)
{
    threadAttrs = ( pthread_attr_t* ) malloc ( sizeof ( pthread_attr_t ) );
    memset ( threadAttrs, 0, sizeof ( pthread_attr_t ) );
    pthread_attr_init ( threadAttrs );
    handle = ( pthread_t* ) malloc ( sizeof ( pthread_t ) );
    memset ( handle, 0, sizeof ( pthread_t ) );
}

Thread::~Thread()
{
    if ( NULL != handle )
    {
        LOG("Freeing handle");
        free ( handle );
    }
    if ( NULL != threadAttrs )
    {
        LOG("Freeing thrattrs");
        pthread_attr_destroy(threadAttrs);
        free ( threadAttrs );
    }
}

/**
 * The thread procedure
 */
void* Thread::thread_proc ( void* parameter )
{
    Thread* theThread = ( Thread* ) parameter;
    return theThread->process();
}

/**
 * Start the thread
 */
bool Thread::start()
{
    int result = pthread_create ( handle, threadAttrs, Thread::thread_proc, this );
    if ( result )
    {
        LOG_ERR ( "could not create a pthread object" );
        return false;
    }
    started = true;
    alive = true;
    return true;
}

/**
 * Stops the thread
 */
bool Thread::stop()
{
    alive = false;

    LOG("Canceling thread");
    pthread_cancel(*handle);

    return true;
}

int Thread::waitToFinish()
{
    return pthread_join( *handle, NULL );

    return 0;
}

void Thread::suspendCurrent ( int msec )
{
#ifdef _WIN32
#ifndef CYGWIN
    Sleep ( msec );
#else
    usleep ( msec * 100 );
#endif
#else
    usleep ( msec * 100 );
#endif
}
