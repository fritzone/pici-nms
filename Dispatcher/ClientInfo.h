#pragma once
#include "local.h"

enum CI_RESPONSE { CI_OK = 0,
                   CI_ERRCANTCONNECT,
                   CI_ERRLOSTCONNECTION,
                   CI_ERRBADRESPONSE,
                   CI_ERRNOMEMREMOTE,
                   CI_ERRNOMEMLOCAL  };

class ClientInfo
{
private:
    io_service* io;
public:
    ClientInfo ( io_service* _io, std::string _ip, int _port, int _number );
    int clientPort;
    std::string clientIp;
    int clientNumber;
    CI_RESPONSE sendMessage ( std::string msg );
    CI_RESPONSE ping();
};

