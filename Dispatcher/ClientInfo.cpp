#include "local.h"
#include "_socket.h"
#include "TCPClient.h"
#include "ExceptionCI.h"
#include "ClientInfo.h"

#include <string>
using namespace std;

ClientInfo::ClientInfo ( io_service* _io, std::string _ip, int _port, int _number ) :
    io ( _io ),
    clientPort ( _port ),
    clientIp ( _ip ),
    clientNumber ( _number )
{
}

CI_RESPONSE ClientInfo::sendMessage ( std::string msg )
{
    LOG ( "ClientInfo::sendMessage entered\n" );
    int bytes, iACK;
    std::string ctlResponse;
    std::string sSize;

    TRY
    {
        TCPClient client ( *io );
        if ( client.Connect ( clientIp, clientPort ) == CONNECTERROR )
        {
            LOG ( "Cannot connect to the client" );
            throw EXCEPTION ( ExceptionCICantConnect );
        }

// FS_SERV1: //sending the message
        {
            LOG ( "FS_SERV1\n" );
            LOG ( "Sending:%s\n", msg.c_str() );
            bytes = client.SendBytes ( msg );
            if ( bytes == SENDERROR )
            {
                throw EXCEPTION ( ExceptionCILostConnection );
            }
        }

// FS_SERV2: //receiving the acknowledgment reply to the message, ie. "-3"
        {
            LOG ( "FS_SERV2\n" );
            bytes = client.ReceiveBytes ( ctlResponse );
            LOG ( "Message sent, received as reply:%s\n", ctlResponse.c_str() );
            if ( bytes == RECVERROR )
            {
                throw EXCEPTION ( ExceptionCILostConnection );
            }
            if ( !strtoi ( ctlResponse, iACK ) )
            {
                throw EXCEPTION ( ExceptionCIBadResponse );
            }
            else if ( iACK == NOT_ENOUGH_MEMORY )
            {
                throw EXCEPTION ( ExceptionCINoMemRemote );
            }
            else if ( iACK != -3 )
            {
                throw EXCEPTION ( ExceptionCIBadResponse );
            }
        }

        LOG ( "SENDMESSAGE_OK\n" );
        return CI_OK; //ASYNC_SEND ends here
    }

    CATCH ( ExceptionCICantConnect & ex )
    {
        EXOUT ( ex );
        return CI_ERRCANTCONNECT;
    }

    CATCH ( ExceptionCIBadResponse & ex )
    {
        EXOUT ( ex );
        return CI_ERRBADRESPONSE;
    }

    CATCH ( ExceptionCILostConnection & ex )
    {
        EXOUT ( ex );
        return CI_ERRLOSTCONNECTION;
    }

    CATCH ( ExceptionCINoMemRemote & ex )
    {
        EXOUT ( ex );
        return CI_ERRNOMEMREMOTE;
    }
}

CI_RESPONSE ClientInfo::ping() //PINGS THE CLIENT
{
    TRY
    {
        int bytes;
        std::string ctlResponse;
        TCPClient client ( *io );
        bytes = client.Connect ( clientIp, clientPort );
        if ( bytes == CONNECTERROR )
        {
            throw EXCEPTION ( ExceptionCICantConnect );
        }
        bytes = client.SendBytes ( PING );
        if ( bytes == SENDERROR )
        {
            throw EXCEPTION ( ExceptionCILostConnection );
        }
        bytes = client.ReceiveBytes ( ctlResponse );
        if ( bytes == RECVERROR )
        {
            throw EXCEPTION ( ExceptionCILostConnection );
        }
        if ( ctlResponse == "PONG" )
        {
            return CI_OK;
        }
        else { throw EXCEPTION ( ExceptionCIBadResponse ); }

    }
    CATCH ( ExceptionCIBadResponse & ex )
    {
        EXOUT ( ex );
        return CI_ERRBADRESPONSE;
    }

    CATCH ( ExceptionCICantConnect & ex )
    {
        EXOUT ( ex );
        return CI_ERRCANTCONNECT;
    }

    CATCH ( ExceptionCILostConnection & ex )
    {
        EXOUT ( ex );
        return CI_ERRLOSTCONNECTION;
    }

}
