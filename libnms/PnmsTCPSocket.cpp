#include "PnmsTCPSocket.h"
#include "Thread.h"
#include "Logger.h"

#include <time.h>
#include <sstream>
#include <iostream>

using namespace std;

/**
 * Sends the command through the wire. Waits for an acknowledgment to be sent from the other side, returns it
 */
string PnmsTCPSocket::send ( CommandInterface* cmd, bool needsAck )
{
    string scmd = cmd->asString();
    if ( !TCPSocket::send ( scmd ) ) // first step: FS_COMM1, sending the message itself
    {
        LOG ( "Could not send message size" );
        return "";
    }
    if ( !needsAck )
    {
        return "DONE";
    }

    Thread::suspendCurrent ( 100 );

    string ack = TCPSocket::receive();  // second step: FS_COMM2, receiving the acknowledgment: message size

    // cout << "[PnmsTCPSocket::send] ack: -->" << ack << "<-- ack \n";
    return ack;
}

string PnmsTCPSocket::send ( CommandInterface* cmd, int timeout )
{
    send ( cmd ); // firstly send the message
    // then wait for the reply .
    time_t startTime, nowTime;
    string reply = "";
    time ( &startTime );
    setNonBlocking();
    bool can_stop = false;
    while ( !can_stop )
    {
        Thread::suspendCurrent ( 100 );
        string replySize = receive();
        if ( replySize.length() > 0 ) // only if we have received a message size
        {
            setBlocking();
            TCPSocket::send ( replySize ); // send it back
            reply = TCPSocket::receive();
            can_stop = true;
        }
        time ( &nowTime );
        if ( nowTime - startTime >= timeout )
        {
            can_stop = true;
        }

    }
    return reply;
}
