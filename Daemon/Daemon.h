#ifndef _DAEMON_H_
#define _DAEMON_H_

#include <string>
#include <vector>

using namespace std;

class ThreadedUDPServer;
class NetworkAddress;
class DaemonUDPServerThread;
class ThreadedTCPServer;
class DaemonInnerTCPServerThread;
class ClientAcceptor;
class InnerTCPClientFactory;
class RegisteredDispatcher;
class DaemonPingerThread;

/**
 * This class holds the implementation of the daemon module, such as configuration loading, threading
 * etc...
 */
class Daemon
{

	friend class DaemonMessageHandler;
	friend class DaemonPingerThread;
	friend class Service;

public:

	/**
	 * Constructor
	 */
	Daemon();

	/**
	 * Destructor
	 */
	virtual ~Daemon();

	/**
	 * Starts the Daemon. Returns true in case of success, false in case of failure
	 */
	bool startup();

private:

	/**
	 * Loads the configuration file and sets up the variables used by the daemon
	 */
	bool loadConfig();

	/**
	 * Initializes the interfaces of the daemon
	 */
	bool initializeInterfaces();

	/**
	 * Creates the UDP Server
	 */
	bool createUDPServer();

	/**
	 * Creates the Inner TCP Server
	 */
	bool createInnerTCPServer();

#ifdef WIN32
	/**
	 * Initialize the Winsock interface
	 */
	bool initWinsock();
#endif

protected:

	/**
	 * Add a dispatcher
	 */
	void addDispatcher(RegisteredDispatcher* tr)
	{
		dispatchers.push_back(tr);
	}

	/**
	 * Removes a dispatcher
	 */
	void removeDispatcher(RegisteredDispatcher* rd);

	/**
	 * Get the vector of transporters as a read only object
	 */
	const vector<RegisteredDispatcher*>& getDispatchers() const
	{
		return dispatchers;
	}

	/**
	 * Verifies the correctness of the sitekey received from the given address
	 */
	bool isValidSitekey(const string& sitekeky, const NetworkAddress* from) const;

	/**
	 * Adds a new dispatcher to the daemon internals
	 */
	bool addDispatcher(const string& ip, const string& port, const string& sitekey);

protected:

	/**
	 * Returns the ID of the next dynamic host
	 */
	static int getNextDynamicHost()
	{
		return dynamicHostCount ++;
	}

	/**
	 * Returns the ID of the next daemon that has connected to this dispatcher
	 */
	static int getNextDispatcherId()
	{
		return dispatcherIdCount ++;
	}

private:

	// the UDP port which receives the broadcast messages
	int udpDaemonPort;

	// the port of the inner networks server
	int tcpInnerDaemonPort;

	// the Threaded UDP Server of the daemon. This is waiting for the connections from not secure clients
	ThreadedUDPServer* udpserv;

	// the network address where the UDP server is bound
	NetworkAddress* udpNetAddr;

	// The Thread of the UDP server
	DaemonUDPServerThread* dups;

	// the server that will "accept" clients from the inner network
	ThreadedTCPServer* innerTCPServer;

	// the thread if the TCP server for the inner network
	DaemonInnerTCPServerThread* daemonInnerThread;

	// the thread pinging the dispatchers
	DaemonPingerThread* pinger;

	// the local TCP client
	InnerTCPClientFactory* innerTcpClFac;

	// the client acceptor
	ClientAcceptor* ca;

	// the IP of the network that will hold the inner communication (meaning, secure clients connect to this net, dispatcher also)
	string innerIP;

	// the vector of client requests
	vector < RegisteredDispatcher * > dispatchers;

private:

	// this counts the dynamic hosts, connected through UDP
	static int dynamicHostCount;

	// counts the attached dispatchers
	static int dispatcherIdCount;

};

#endif
