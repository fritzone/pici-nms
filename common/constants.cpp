#include "constants.h"

const char* COMMAND_NMS_INIT     = "NMS_INIT";
const char* COMMAND_NOINIT       = "NOINIT";
const char* COMMAND_NMS_OK       = "NMS_OK";
const char* COMMAND_HELLO        = "HELLO";
const char* COMMAND_MESSAGE      = "MESSAGE";
const char* COMMAND_SUBSCRIBE    = "SUBSCRIBE";
const char* COMMAND_UNSUBSCRIBE  = "UNSUBSCRIBE";
const char* COMMAND_DSP_PING 	= "DSP_PING";
const char* STR_ERROR            = "ERROR";
const char* STR_NO_RESPONSE      = "NO_RESPONSE";

const char COMMAND_SEPARATOR1    = '#';
const char COMMAND_SEPARATOR2    = ':';
const char COMMAND_SEPARATOR3    = '@';

const char* CONFIG_DISPATCHER_PROTOCOL   = "tcp";
const char* CONFIG_DISPATCHER_PORT       = "7566";

int DISPATCHER_PORT              = 7566;

const char* STR_SYNCH            = "SYNCH";
const char* STR_ASYNCH           = "ASYNCH";

const char* ERR_NOTREADY         = "The network susbsystem is not ready";
const char* ERR_VERNOTSUPPORTED  = "The requested version is not supported";
const char* ERR_BLOCKINPROGRESS  = "A blocking Winsock1.1 op. in progress";
const char* ERR_PROCLIM          = "Maximum limit of Socket tasks reached";
const char* ERR_EFAULT           = "Invalid address for WSADATA";
const char* ERR_NO               = "All is ok";

const char* ERR_NETDOWN          = "The network subsystem or the associated service provider has failed.";
const char* ERR_NOSUPPORT        = "The specified address family is not supported.";
const char* ERR_NOMORESOCK       = "No more socket descriptors are available";
const char* ERR_NOBUF            = "No buffer space is available";
const char* ERR_NOSOCKTSUPP      = "The specified socket type is not supported in this address family";
const char* ERR_WRONGPROTOTYPE   = "The specified protocol is the wrong type for this socket";
const char* ERR_WRONGPROTOCOL    = "The specified protocol is not supported";

const char* DISPATCHER_MUTEX     = "dispatcherMutex";
const char* QUEUE_MUTEX          = "queueMutex";
const char* PONG                 = "PONG";
const char* PING                 = "PING";
const char* ACK                  = "ACK";

const char* STR_FIELD_ERROR      = "$ERROR";
const char* STR_FIELD_TIMEOUT    = "$TIMEOUT";

const char* ERR_CANNOT_CREATE_SOCKET             = "Cannot create socket to dispatcher";
const char* ERR_CANNOT_SEND_DATA_SIZE            = "Could not send data size to dispatcher";
const char* ERR_CANNOT_RECEIVE_DATA_SIZE_ACK     = "Could not receive acknowledgement to msg size";
const char* ERR_SIZE_NOT_EQUAL                   = "Received acknowledgement size is not equal to original size";
const char* ERR_CANNOT_SEND_DATA                 = "Could not send data to transporter";
const char* ERR_CANNOT_RECEIVE_MSG_SIZE_ACK      = "Could not receive acknowledgement as received message size";
const char* ERR_NOT_ENOUGH_MEMORY                = "Not enough memory for input buffer";
const char* ERR_CANNOT_SEND_SIZE_ACK             = "Cannot send size acknowledgement";
const char* ERR_CANNOT_RECEIVE_SYNCH_RESPONSE    = "Cannot receive synch message";
const char* ERR_UNKNOWN                          = "Unknown Error";
const char* ERR_TIMEOUT                          = "Timeout";
const char* ERR_COMMUNICATION                    = "Communication error";

string DIRSEP()
{
#ifdef _WIN32
    return string ( "\\" );
#else
    return string ( "/" );
#endif
}
