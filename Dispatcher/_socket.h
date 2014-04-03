#pragma once

#ifdef WIN32
	#define CLOSESOCKET closesocket
	#define INET_ATON(x,y) ( y.s_addr = inet_addr(x) )
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <errno.h>
	#include <resolv.h>

	#define INVALID_SOCKET -1
	#define CLOSESOCKET close
	#define INET_ATON( ascii_form, sin_form ) inet_aton( ascii_form, sin_form )
	typedef int SOCKET;
#endif

#define NEWSOCKET socket
#define SEND ::send
#define RECV ::recv
#define CONNECT ::connect
#define HTONS htons

#define CONNECTOK 1
#define CONNECTERROR -1
#define RECVERROR -1
#define SENDERROR -1


