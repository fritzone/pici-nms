#ifndef __DAEMONMUTEX_H_
#define __DAEMONMUTEX_H_

#include <pthread.h>

class Mutex {

private:
    
	pthread_mutex_t Dmutex;
    pthread_mutexattr_t attr;

private:
	Mutex(const Mutex&);
	Mutex& operator= (const Mutex&);

public:
    Mutex();
    int lock();
    int unlock();
};

#endif
