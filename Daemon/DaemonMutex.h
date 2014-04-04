#ifndef __DAEMONMUTEX_H_
#define __DAEMONMUTEX_H_

#include <pthread.h>

class DaemonMutex
{

private:

    pthread_mutex_t Dmutex;
    pthread_mutexattr_t attr;

private:
    DaemonMutex ( const DaemonMutex& );
    DaemonMutex& operator= ( const DaemonMutex& );

public:
    DaemonMutex();
    int lock();
    int unlock();
};

#endif
