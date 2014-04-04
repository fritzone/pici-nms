#include "ThreadPinger.h"
#include "Service.h"

#undef MSEC_PING_SLEEP_TIME
#define MSEC_PING_SLEEP_TIME 5

void ThreadPinger()
{
    while ( true )
    {
        SLEEP ( 5 );
        // firstly "hack" the not ping status. A pinged() event will anyway solve this.
        Service::getMe()->notPinged();
        if ( Service::getMe()->getPingCounter() > 5 )
        {
            LOG ( "Daemon highly possible disappeared... trying to re-register\n" );
            if ( !Service::getMe()->registerToDaemon() )
            {
                LOG ( "Cannot register to the daemon this run, retrying in 5 seconds\n" );
            }
            else
            {
                LOG ( "Succesfully re-registered\n" );
                Service::getMe()->pinged();
            }
        }

        LOG ( "ThreadPinger(): Loop\n" );
        SCOPEDLOCK ( dispatcherMutex );
        for ( STL_SUBSCRIPTIONINFO::iterator it = subscriptions.begin(); it != subscriptions.end(); )
        {
            CI_RESPONSE response = ( *it )->ci->ping();
            if ( response == CI_ERRCANTCONNECT )
            {
                LOG ( "ThreadPinger() : ERROR PINGING '%s'. REMOVING IT.\n", C_STR ( ( *it )->ci->clientIp ) );
                delete ( *it );
                it = subscriptions.erase ( it );
            }
            else
            {
                it++;
            }
        }
    }
}
