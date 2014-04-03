#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <string>

using namespace std;


/**
 * PICI/NMS Commands
 * \defgroup ERROR_CODES
 *
 *	PICI/NMS Commands
 *  @{
 */
static const char* COMMAND_NMS_INIT		= "NMS_INIT";
static const char* COMMAND_NOINIT		= "NOINIT";
static const char* COMMAND_NMS_OK		= "NMS_OK";
static const char* COMMAND_HELLO		= "HELLO";
static const char* COMMAND_MESSAGE		= "MESSAGE";
static const char* COMMAND_SUBSCRIBE	= "SUBSCRIBE";
static const char* COMMAND_UNSUBSCRIBE	= "UNSUBSCRIBE";
static const char* STR_ERROR			= "ERROR";
static const char* STR_NO_RESPONSE		= "NO_RESPONSE";

static const char COMMAND_SEPARATOR1	= '#';
static const char COMMAND_SEPARATOR2	= ':';
static const char COMMAND_SEPARATOR3	= '@';

/*@}*/
	
/**
 * PICI/NMS Settings
 * \defgroup ERROR_CODES
 *
 *	PICI/NMS Settings
 *  @{
 */
static const char* CONFIG_DISPATCHER_PROTOCOL	= "tcp";
static const char* CONFIG_DISPATCHER_PORT		= "7566";

const int DAEMON_PORT			= 5150;
const int STARTING_TCP_PORT		= 45000;
const int LAST_CHECKED_TCP_PORT	= 65530;
const int DISPATCHER_PORT		= 7566;

const int SEC_WAIT_FOR_DAEMON	= 10;
const int MSEC_PING_SLEEP_TIME	= 5000;
const int MSEC_QUEUE_SLEEP_TIME	= 10000;
/*@}*/

/**
 * Message Types
 * \defgroup ERROR_CODES
 *
 *	Message Types
 *  @{
 */
static const char* STR_SYNCH	= "SYNCH";
static const char* STR_ASYNCH	= "ASYNCH";
/*@}*/


// these messages can appear while calling WSAStartup
static const char* ERR_NOTREADY			= "The network susbsystem is not ready";
static const char* ERR_VERNOTSUPPORTED	= "The requested version is not supported";
static const char* ERR_BLOCKINPROGRESS	= "A blocking Winsock1.1 op. in progress";
static const char* ERR_PROCLIM			= "Maximum limit of Socket tasks reached";
static const char* ERR_EFAULT			= "Invalid address for WSADATA";
static const char* ERR_NO				= "All is ok";

/// these messages can appear, while calling socket()
static const char* ERR_NETDOWN			= "The network subsystem or the associated service provider has failed.";
static const char* ERR_NOSUPPORT		= "The specified address family is not supported.";
static const char* ERR_NOMORESOCK		= "No more socket descriptors are available";
static const char* ERR_NOBUF			= "No buffer space is available";
static const char* ERR_NOSOCKTSUPP		= "The specified socket type is not supported in this address family";
static const char* ERR_WRONGPROTOTYPE	= "The specified protocol is the wrong type for this socket";
static const char* ERR_WRONGPROTOCOL	= "The specified protocol is not supported";

// strigs used in the program
static const char* DISPATCHER_MUTEX		= "dispatcherMutex";
static const char* QUEUE_MUTEX			= "queueMutex";
static const char* PONG					= "PONG";
static const char* PING					= "PING";
static const char* ACK					= "ACK";

/**
 * Field Codes for messages
 * \defgroup FIELDCODES
 *
 *	PICI/NMS Field Codes
 *  @{
 */

/// The String, which identifies an error field. Type: DT_STRING
static const char* STR_FIELD_ERROR		= "$ERROR";
/// The String, whcih identifies the timeout field. Type: DT_INT
static const char* STR_FIELD_TIMEOUT	= "$TIMEOUT";
/*@}*/


/**
 * Messages from different parts of program
 * \defgroup MESSAGES
 *
 *	PICI/NMS Error Messages
 *  @{
 */
static const char* ERR_CANNOT_CREATE_SOCKET				= "Cannot create socket to dispatcher";
static const char* ERR_CANNOT_SEND_DATA_SIZE			= "Could not send data size to dispatcher";
static const char* ERR_CANNOT_RECEIVE_DATA_SIZE_ACK		= "Could not receive acknowledgement to msg size";
static const char* ERR_SIZE_NOT_EQUAL					= "Received acknowledgement size is not equal to original size";
static const char* ERR_CANNOT_SEND_DATA					= "Could not send data to transporter";
static const char* ERR_CANNOT_RECEIVE_MSG_SIZE_ACK		= "Could not receive acknowledgement as received message size";
static const char* ERR_NOT_ENOUGH_MEMORY				= "Not enough memory for input buffer";
static const char* ERR_CANNOT_SEND_SIZE_ACK				= "Cannot send size acknowledgement";
static const char* ERR_CANNOT_RECEIVE_SYNCH_RESPONSE	= "Cannot receive synch message";
static const char* ERR_UNKNOWN							= "Unknown Error";
static const char* ERR_TIMEOUT							= "Timeout";
static const char* ERR_COMMUNICATION					= "Communication error";

static string DIRSEP()
{
#ifdef WIN32
	return string("\\");
#else
	return string("/");
#endif
}

#endif
