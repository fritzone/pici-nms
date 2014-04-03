#ifndef _SOCKET_ERROR_CODES_H_
#define _SOCKET_ERROR_CODES_H_

/**
 * Simple class sending back the error description according to an error code
 */
class SocketErrorCodes
{
public:

#ifndef WIN32

	static const int OPERATION_BIND 		= 	1;
	static const int OPERATION_CLOSE 		= 	2;
	static const int OPERATION_IOCTL 		= 	4;
	static const int OPERATION_SENDTO		=	8;
	static const int OPERATION_SOCKET		=	16;
	static const int OPERATION_SETSOCKOPT	=	32;
	static const int OPERATION_LISTEN		=	64;
	static const int OPERATION_SEND		=	128;
	static const int OPERATION_CONNECT	=	256;
	
#endif	
	
	/**
	 * Returns the error description for the given error code. Under linux/unix
	 * we support the operation which caused this error
	 */
	static const char* const getErrorDescription(int errorCode
	#ifndef WIN32
		, int requestOperation
	#endif
	);
};

#endif
