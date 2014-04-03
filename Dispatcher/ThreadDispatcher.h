#pragma once
#include "Dispatcher.h"
#include "TCPClient.h"

void ThreadDispatcher();
void DO_DISPATCH(TCPClient* sock);
void DO_CMDHELLO( TCPClient* sock, std::string& message );
void DO_CMDMESSAGE( TCPClient* sock, std::string& message );
void DO_CMDSUBSCRIBE( TCPClient* sock, std::string& message );
void DO_CMDUNSUBSCRIBE( TCPClient* sock, std::string& message );
