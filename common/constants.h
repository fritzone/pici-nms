#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <string>

using namespace std;


/**
 * PICI/NMS Commands
 * \defgroup ERROR_CODES
 *
 *  PICI/NMS Commands
 *  @{
 */
extern const char* COMMAND_NMS_INIT;
extern const char* COMMAND_NOINIT;
extern const char* COMMAND_NMS_OK;
extern const char* COMMAND_HELLO;
extern const char* COMMAND_MESSAGE;
extern const char* COMMAND_SUBSCRIBE;
extern const char* COMMAND_UNSUBSCRIBE;
extern const char* COMMAND_DSP_PING;
extern const char* STR_ERROR;
extern const char* STR_NO_RESPONSE;

extern const char COMMAND_SEPARATOR1;
extern const char COMMAND_SEPARATOR2;
extern const char COMMAND_SEPARATOR3;

/*@}*/

/**
 * PICI/NMS Settings
 * \defgroup ERROR_CODES
 *
 *  PICI/NMS Settings
 *  @{
 */
extern const char* CONFIG_DISPATCHER_PROTOCOL;
extern const char* CONFIG_DISPATCHER_PORT;

const int DAEMON_PORT           = 5150;
const int STARTING_TCP_PORT     = 45000;
const int LAST_CHECKED_TCP_PORT = 65530;
extern int DISPATCHER_PORT;

const int SEC_WAIT_FOR_DAEMON   = 10;
const int MSEC_PING_SLEEP_TIME  = 5000;
const int MSEC_QUEUE_SLEEP_TIME = 10000;
/*@}*/

/**
 * Message Types
 * \defgroup ERROR_CODES
 *
 *  Message Types
 *  @{
 */
extern const char* STR_SYNCH;
extern const char* STR_ASYNCH;
/*@}*/


// these messages can appear while calling WSAStartup
extern const char* ERR_NOTREADY;
extern const char* ERR_VERNOTSUPPORTED;
extern const char* ERR_BLOCKINPROGRESS;
extern const char* ERR_PROCLIM;
extern const char* ERR_EFAULT;
extern const char* ERR_NO;

/// these messages can appear, while calling socket()
extern const char* ERR_NETDOWN;
extern const char* ERR_NOSUPPORT;
extern const char* ERR_NOMORESOCK;
extern const char* ERR_NOBUF;
extern const char* ERR_NOSOCKTSUPP;
extern const char* ERR_WRONGPROTOTYPE;
extern const char* ERR_WRONGPROTOCOL;

// strigs used in the program
extern const char* DISPATCHER_MUTEX;
extern const char* QUEUE_MUTEX;
extern const char* PONG;
extern const char* PING;
extern const char* ACK;

/**
 * Field Codes for messages
 * \defgroup FIELDCODES
 *
 *  PICI/NMS Field Codes
 *  @{
 */

/// The String, which identifies an error field. Type: DT_STRING
extern const char* STR_FIELD_ERROR;
/// The String, whcih identifies the timeout field. Type: DT_INT
extern const char* STR_FIELD_TIMEOUT;
/*@}*/

/**
 * Error codes
 * \defgroup ERROR_CODES
 *
 *  PICI/NMS Error Codes
 *  @{
 */
const int INTERNAL_ERROR        = -7;
const int TIMEOUT               = -6;
const int MALFORMED_RESPONSE    = -4;
const int WRONG_NUMBER          = -5;
const int NO_RESPONSE           = -3;
const int NOT_ENOUGH_MEMORY     = -1;

/*@}*/

/**
 * Messages from different parts of program
 * \defgroup MESSAGES
 *
 *  PICI/NMS Error Messages
 *  @{
 */
extern const char* ERR_CANNOT_CREATE_SOCKET;
extern const char* ERR_CANNOT_SEND_DATA_SIZE;
extern const char* ERR_CANNOT_RECEIVE_DATA_SIZE_ACK;
extern const char* ERR_SIZE_NOT_EQUAL;
extern const char* ERR_CANNOT_SEND_DATA;
extern const char* ERR_CANNOT_RECEIVE_MSG_SIZE_ACK;
extern const char* ERR_NOT_ENOUGH_MEMORY;
extern const char* ERR_CANNOT_SEND_SIZE_ACK;
extern const char* ERR_CANNOT_RECEIVE_SYNCH_RESPONSE;
extern const char* ERR_UNKNOWN;
extern const char* ERR_TIMEOUT;
extern const char* ERR_COMMUNICATION;

string DIRSEP();

#endif
