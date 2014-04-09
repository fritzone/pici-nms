#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

/**
 * Class representing a thread.
 */
class Thread
{
public:
    /**
     * Constructor. Creates a Thread object but does not start it yet.
     */
    Thread();

    /**
     * Destructor
     */
    virtual ~Thread();

    /**
     * Starts the thread
     */
    bool start();

    /**
     * Stops the thread
     */
    bool stop();

    /**
     * Tells us if this thread was started already or not
     */
    bool isStarted() const
    {
        return started;
    }

    /**
     * Thread class derivates should make their loop based on this "alive" member
     */
    bool isAlive() const
    {
        return alive;
    }

    /**
     * Suspends the calling thread to wait for this thread to finish what it's doing
     */
    int waitToFinish();

public:

    /**
     * Suspends the current thread the given number of milliseconds.
     */
    static void suspendCurrent ( int msec );

protected:
    /**
     * The Thread procedure that is being called when a new thread is created. Its role is to call the
     * process method of the parameter which is an object derived from the Thread class.
     */
    static void* thread_proc ( void* parameter );

    /**
     * This method must be overridden by thread classes
     */
    virtual void* process() = 0;

private:

    // the thread's handle returned by the CreateThread method
    pthread_t* handle;

    // the attributes of the thread
    pthread_attr_t* threadAttrs;

    // the thread ID returned by the same
    int tid;

    // true if this thread was started
    bool started;

    // set to true when the "start" method was called, set to false when the "stop" method was called
    bool alive;
};

#endif
