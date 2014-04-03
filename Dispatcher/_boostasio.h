#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define NAME(x) x
#define TCPACCEPTOR(name,ioservice,port) tcp::acceptor name(ioservice, tcp::endpoint(tcp::v4(), port))
#define IOSERVICE(name) boost::asio::io_service name
#define ENDPOINT(host, port) boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string(host),port)

