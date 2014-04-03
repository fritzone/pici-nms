#ifndef _WIN2LINCNV_H_
#define _WIN2LINCNV_H_

#ifndef WIN32

	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/ioctl.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>

	#define SOCKET int
	#define BOOL int
	#define TRUE 1
	#define FALSE 0
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define DWORD unsigned long
	#define SOCKADDR_IN struct sockaddr_in
	#define SOCKADDR struct sockaddr
	#define HOSTENT struct hostent

#endif


#endif
