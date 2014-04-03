#ifndef _DAEMON_MESSAGE_HANDLER_THREAD_H_
#define _DAEMON_MESSAGE_HANDLER_THREAD_H_

#include "Thread.h"
#include "NetworkAddress.h"

#include <string>

using namespace std;

class Daemon;
class DaemonMutex;

/**
 * An instance of this class is created when the daemon receives a message from somewhere that must be handled.
 * The reason for implementing a message handling in a thread is that some messages might take longer,
 * such as connect to database, connect to dispatcher, connect to the outside world, etc...
 */
class DaemonMessageHandlerThread : public Thread
{
public:

	/**
	 * Constructor
	 */
	DaemonMessageHandlerThread(Daemon* dmn);

	/**
	 * Handles the message in a new thread.
	 */
	bool handleMessage(string message, NetworkAddress fromAddr);

protected:

	/**
	 * Processes one message, then ends
	 */
	virtual void *process();

private:

	/**
	 * Checks if the message is an INIT message or not
	 */
	bool isInitMessage(const string& s);

private:

	/**
	* Handles the NMS_INIT message
	*/
	bool handleInitMessage(const string s, NetworkAddress* fromAddr);

private:

	// the daemon
	Daemon* daemon;

	// the message that will be handled in the thread
	string msg;

	// the address from which we've got this message
	NetworkAddress addrs;

	static DaemonMutex messageMutex;
};

#endif
