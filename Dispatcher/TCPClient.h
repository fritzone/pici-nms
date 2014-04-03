#pragma once

#include "local.h"
#include "_socket.h"

using boost::asio::ip::tcp;
using boost::asio::io_service;

using boost::system::error_code;


class TCPClient
{
	protected:
		tcp::socket* _me;
	public:
		TCPClient();
		TCPClient( io_service& io);
		TCPClient( io_service& io, std::string host, int port);
		TCPClient( tcp::socket* sock );
		~TCPClient();
		void Close();
		int Connect( std::string host, int port );
		int SendBytes( std::string const& s );
		int ReceiveLine( std::string& retStr );
		int ReceiveBytes( std::string& ret );
		operator tcp::socket*() const;
};


