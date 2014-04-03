#include "SocketErrorCodes.h"

#ifdef WIN32
	#include <WinSock2.h>
#else
	#include <errno.h>
#endif
/**
 * Returns the error description ofthe error code
 */
const char* const SocketErrorCodes::getErrorDescription(int errorCode
												#ifndef WIN32
												, int requestOperation
												#endif
)
{
#ifdef WIN32
	switch(errorCode)
	{
	case WSAEINTR:				return "Interrupted function call (WSAEINTR)";
	case WSAEACCES:				return "Permission denied (WSAEACCES)";
	case WSAEFAULT:				return "Bad address (WSAEFAULT)";
	case WSAEINVAL:				return "Invalid argument (WSAEINVAL)";
	case WSAEMFILE:				return "Too many open files (WSAEMFILE)";
	case WSAEWOULDBLOCK:		return "Resource temporarily unavailable (WSAEWOULDBLOCK)";
	case WSAEINPROGRESS:		return "Operation now in progress (WSAEINPROGRESS)";
	case WSAEALREADY:			return "Operation already in progress (WSAEALREADY)";
	case WSAENOTSOCK:			return "Socket operation on nonsocket (WSAENOTSOCK)";
	case WSAEDESTADDRREQ:		return "Destination address required (WSAEDESTADDRREQ)";
	case WSAEMSGSIZE:			return "Message too long (WSAEMSGSIZE)";
	case WSAEPROTOTYPE:			return "Protocol wrong type for socket (WSAEPROTOTYPE)";
	case WSAENOPROTOOPT:		return "Bad protocol option (WSAENOPROTOOPT)";
	case WSAEPROTONOSUPPORT:	return "Protocol not supported (WSAEPROTONOSUPPORT)";
	case WSAESOCKTNOSUPPORT:	return "Socket type not supported (WSAESOCKTNOSUPPORT)";
	case WSAEOPNOTSUPP:			return "Operation not supported (WSAEOPNOTSUPP)";
	case WSAEPFNOSUPPORT:		return "Protocol family not supported (WSAEPFNOSUPPORT)";
	case WSAEAFNOSUPPORT:		return "Address family not supported by protocol family (WSAEAFNOSUPPORT)";
	case WSAEADDRINUSE:			return "Address already in use (WSAEADDRINUSE)";
	case WSAEADDRNOTAVAIL:		return "Cannot assign requested address (WSAEADDRNOTAVAIL)";
	case WSAENETDOWN:			return "Network is down (WSAENETDOWN)";
	case WSAENETUNREACH:		return "Network is unreachable (WSAENETUNREACH)";
	case WSAENETRESET:			return "Network dropped connection on reset (WSAENETRESET)";
	case WSAECONNABORTED:		return "Software caused connection abort (WSAECONNABORTED)";
	case WSAECONNRESET:			return "Connection reset by peer (WSAECONNRESET)";
	case WSAENOBUFS:			return "No buffer space available (WSAENOBUFS)";
	case WSAEISCONN:			return "Socket is already connected (WSAEISCONN)";
	case WSAENOTCONN:			return "Socket is not connected (WSAENOTCONN)";
	case WSAESHUTDOWN:			return "Cannot send after socket shutdown (WSAESHUTDOWN)";
	case WSAETIMEDOUT:			return "Connection timed out (WSAETIMEDOUT)";
	case WSAECONNREFUSED:		return "Connection refused (WSAECONNREFUSED)";
	case WSAEHOSTDOWN:			return "Host is down (WSAEHOSTDOWN)";
	case WSAEHOSTUNREACH:		return "No route to host (WSAEHOSTUNREACH)";
	case WSAEPROCLIM:			return "Too many processes (WSAEPROCLIM)";
	case WSASYSNOTREADY:		return "Network subsystem is unavailable (WSASYSNOTREADY)";
	case WSAVERNOTSUPPORTED:	return "Winsock.dll version out of range (WSAVERNOTSUPPORTED)";
	case WSANOTINITIALISED:		return "Successful WSAStartup not yet performed (WSANOTINITIALISED)";
	case WSAEDISCON:			return "Graceful shutdown in progress (WSAEDISCON)";
	case WSATYPE_NOT_FOUND:		return "Class type not found (WSATYPE_NOT_FOUND)";
	case WSAHOST_NOT_FOUND:		return "Host not found (WSAHOST_NOT_FOUND)";
	case WSATRY_AGAIN:			return "Nonauthoritative host not found (WSATRY_AGAIN)";
	case WSANO_RECOVERY:		return "This is a nonrecoverable error (WSANO_RECOVERY)";
	case WSANO_DATA:			return "Valid name, no data record of requested type (WSANO_DATA)";
	case WSA_INVALID_HANDLE:	return "Specified event object handle is invalid (WSA_INVALID_HANDLE)";
	case WSA_INVALID_PARAMETER:	return "One or more parameters are invalid (WSA_INVALID_PARAMETER)";
	case WSA_IO_INCOMPLETE:		return "Overlapped I/O event object not in signaled state (WSA_IO_INCOMPLETE)";
	case WSA_IO_PENDING:		return "Overlapped operations will complete later (WSA_IO_PENDING)";
	case WSA_NOT_ENOUGH_MEMORY:	return "Insufficient memory available (WSA_NOT_ENOUGH_MEMORY)";
	case WSA_OPERATION_ABORTED:	return "Overlapped operation aborted (WSA_OPERATION_ABORTED)";
	case WSASYSCALLFAILURE:		return "System call failure (WSASYSCALLFAILURE)";
	}

	return "Not found ...";
#else
	switch(requestOperation)
	{
			// errors that are raised by the bind command
		case OPERATION_BIND:
			switch(errorCode)
			{
			case EACCES:				return "Address protected, user not root or search permission denied (EACCES)";
			case EBADF:					return "Not a valid socket descriptor (EBADF)";
			case EINVAL:				return "Socket already bound or addrlen for bind is wrong or socket is not AF_UNIX (EINVAL)";
			case EADDRINUSE:			return "Address already used (EADDRINUSE)";
			case ENOTSOCK:				return "File descriptor called with bind, not socket (ENOTSOCK)";
			case EADDRNOTAVAIL:			return "Nonexistent interface was requested or the address is not local (EADDRNOTAVAIL)";
			case EFAULT:				return "The address points outside the user's accessible address space/overflow? (EFAULT)";
			case ELOOP:					return "Too many symbolic links were encountered in resolving addr. (ELOOP)";
			case ENAMETOOLONG:			return "Addr for bind is too long (ENAMETOOLONG)";
			case ENOENT:				return "The file does not exist (ENOENT)";
			case ENOMEM:				return "Insufficient kernel memory was available (ENOMEM)";
			case ENOTDIR:				return "A component of the path prefix is not a directory (ENOTDIR)";
			case EROFS:					return "The socket inode would reside on a read-only file system (EROFS)";
			default:					return "Unknown error in bind"; 
			}
			
			// errors that are raised by the close command
		case OPERATION_CLOSE:
			switch(errorCode)
			{
			case EBADF:					return "The fd isn't a valid open file descriptor (EBADF)";
			case EINTR:					return "The close() call was interrupted by a signal (EINTR)";
			case EIO:					return "An I/O error occurred (EIO)";
			default:					return "Unknown error while close-ing something";
			}
			
			// errors raised by ioctl
		case OPERATION_IOCTL:
			switch(errorCode)
			{
			case EBADF:					return "The descriptor (d) is not valid (EBADF)";
			case EFAULT:				return "argp references an inaccessible memory area (EFAULT)";
			case EINVAL:				return "Request or argp is not valid (EINVAL)";
			case ENOTTY:				return "The decriptor (d) is not associated with a character special device/ The specified request does not apply to the kind of object that the descriptor d references (ENOTTY)";
			default:					return "Unknown error while ioctl-ing";
			}
			
			// errors caused by the sendto command
		case OPERATION_SENDTO:
			switch(errorCode)
			{
			case EACCES: 				return "Write permission is denied on the destination socket file, or search permission is denied for one of the directories the  path  prefix (EACCESS)";
			case EWOULDBLOCK:			return "The socket is marked non-blocking and the requested operation would block (EAGAIN/EWOULDBLOCK)";
			case EBADF:  				return "An invalid descriptor was specified (EBADF)";
			case ECONNRESET:			return "Connection reset by peer. (ECONNRESET)";
			case EDESTADDRREQ:			return "The socket is not connection-mode, and no peer address is set (EDESTADDRREQ)";
			case EFAULT: 				return "An invalid user space address was specified for an argument (EFAULT)";
			case EINTR:  				return "A signal occurred before any data was transmitted (EINTR)";
			case EINVAL: 				return	"Invalid argument passed (EINVAL)";
			case EISCONN:				return "The  connection-mode socket was connected already but a recipient was specified (EISCONN)";
			case EMSGSIZE:				return "The socket type requires that message be sent atomically, and the size of the message to  be  sent made this impossible (EMSGSIZE)";
			case ENOBUFS:				return "The  output  queue  for a network interface was full (ENOBUFS)";
			case ENOMEM: 				return "No memory available (ENOMEM)";
			case ENOTCONN:				return "The socket is not connected, and no target has been given (ENOTCONN)";
			case ENOTSOCK:				return "The argument sockfd is not a socket (ENOTSOCK)";
			case EOPNOTSUPP:			return "Some bit in the flags argument is inappropriate for the socket type (EOPNOTSUPP)";
			case EPIPE:  				return "The  local  end has been shut down on a connection oriented socket (EPIPE)";
			default:					return "Unknow sendto error";				
			}
			
			// errors caused by the socket command
		case OPERATION_SOCKET:
			switch(errorCode)
			{
			case EACCES: 				return "Permission to create a socket of the specified type and/or protocol is denied (EACCES)";
			case EAFNOSUPPORT:			return "The implementation does not support the specified address family (EAFNOSUPPORT)";
			case EINVAL: 				return "Unknown protocol, or protocol family not available / Invalid flags in type (EINVAL)";
			case EMFILE: 				return "Process file table overflow (EMFILE)";
			case ENFILE: 				return "The system limit on the total number of open files has been reached (ENFILE)";
			case ENOBUFS:
			case ENOMEM:				return "Insufficient memory is available.  The socket cannot be created  until  sufficient  resources  are freed (ENOMEM)";
			case EPROTONOSUPPORT:		return "The protocol type or the specified protocol is not supported within this domain (EPROTONOSUPPORT)";
			default:					return "Unknown socket error";
			}
	}
	
	return "Not implemented";
#endif
}
