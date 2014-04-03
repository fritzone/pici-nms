#ifndef _DAEMON_MESSAGE_HANDLER_H_
#define _DAEMON_MESSAGE_HANDLER_H_

#include <string>

using namespace std;

class NetworkAddress;
class Daemon;
class AbstractSocket;

/**
 * This class handles the messages that are sent to the daemon
 */
class DaemonMessageHandler
{
public:

	/**
	 * Handles the message. Calls the specific message handler function for now
	 */
	static bool handleMessage(const std::string& s, NetworkAddress* fromAddr, Daemon* daemon, AbstractSocket* respSock);

private:

	/**
	 * Returns true if this is an init message (NMS_INIT)
	 */
	static bool isInitMessage(const string& s);

	/**
	 * Returns true if this is a Dispatcher init message (DSP_INIT)
	 */
	static bool isDispInitMessage(const string& s);

	/**
	 * Handles the init message. 
	 */
	static bool handleInitMessage(const std::string& s, NetworkAddress* fromAddr, Daemon* daemon, AbstractSocket* respSock);

	/**
	 * Handles the init message. 
	 */
	static bool handleDispInitMessage(const std::string& s, NetworkAddress* fromAddr, Daemon* daemon, AbstractSocket* respSock);

	/**
	 * Generates a new sitekey from the old one
	 */
	static string generateNewSitekey(const string& oldSitekey);


};

#endif
