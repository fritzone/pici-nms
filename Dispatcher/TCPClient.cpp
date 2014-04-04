#include "TCPClient.h"

//
#undef  LOG
#define LOG(...) (void)0


TCPClient::TCPClient ( io_service& io ) : _me ( new tcp::socket ( io ) )
{
    LOG ( "TCPClient::TCPClien( io_service& io)\n" );
}

TCPClient::TCPClient ( io_service& io, std::string host, int port ) : _me ( new tcp::socket ( io ) )
{
    LOG ( "TCPClient::TCPClient( io_service& io, std::string host, int port)\n" );
    Connect ( host, port );
}

TCPClient::TCPClient ( tcp::socket* sock ) : _me ( sock )
{
    LOG ( "TCPClient::TCPClient( tcp::socket* sock )\n" );
}

TCPClient::TCPClient()
{
    LOG ( "TCPClient::TCPClient()\n" );
}

TCPClient::~TCPClient()
{
    Close();
}

void TCPClient::Close()
{
    LOG ( "TCPClient::~TCPClient()\n" );
    _me->close();
    //delete _me;
}

int TCPClient::Connect ( std::string host, int port )
{
    LOG ( "TCPClient::Connect('%s',%d)\n", C_STR ( host ), port );
    error_code error;
    _me->connect ( ENDPOINT ( host, port ), error );
    if ( error )
    {
        LOG ( "TCPClient::Connect('%s',%d) : CONNECT ERROR\n", C_STR ( host ), port );
        return CONNECTERROR;

    }
    else
    {
        LOG ( "TCPClient::Connect('%s',%d) : CONNECT OK\n", C_STR ( host ), port );
        return CONNECTOK;
    }
}

int TCPClient::SendBytes ( std::string const& s )
{
    LOG ( "TCPClient::SendBytes Sending --[%s]--\n", s.c_str() );
    size_t ret = boost::asio::write ( *_me, boost::asio::buffer ( C_DATA ( s ), C_LEN ( s ) ) );
    LOG ( "TCPClient::SendBytes: ret(%d)\n", ret );
    if ( ret < C_LEN ( s ) )
    {
        return SENDERROR;
    }
    return ret;
}

int TCPClient::ReceiveLine ( std::string& retStr )
{
    boost::system::error_code error;
    boost::asio::streambuf response;
    CLEAR ( retStr );
    int retBytes = boost::asio::read_until ( *_me, response, '\n', error );
    if ( error == boost::asio::error::eof )
    {
        return  retBytes;    //Connection closed cleanly by peer.
    }
    else if ( error )
    {
        return RECVERROR;    // Some other error.
    }

    return 0;
}

int TCPClient::ReceiveBytes ( std::string& ret )
{
    // I have modified the line below, since long messages did not come through :(
    boost::array<char, 65536> buf;
    boost::system::error_code error;
    int retBytes = 0, recvBytes = 0;
    recvBytes = _me->read_some ( boost::asio::buffer ( buf ), error );
    ret.assign ( buf.data(), recvBytes );
    retBytes += recvBytes;
    LOG ( "Received ----[%s]----\n", ret.c_str() );
    if ( error )
        if ( error != boost::asio::error::eof )
        {
            LOG ( "TCPClient::ReceiveBytes: ERROR\n" );
            return RECVERROR;
        }

    LOG ( "TCPClient::ReceiveBytes( %d ):  no ERROR\n", retBytes );
    return retBytes; //Connection closed cleanly by peer.

}

TCPClient::operator tcp::socket* () const
{
    return _me;
}

