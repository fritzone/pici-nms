#include "Service.h"
#include "ConfigReader.h"
#include "CommandUtils.h"

Service* Service::me = NULL;

/**
 * Servie constructor
 */
Service::Service ( const char* serviceName, ConfigReader& cfg ) :  pingCounter ( 0 ),
    ServiceName ( serviceName ? serviceName : "_anonymous" )
{
    LOG ( "Service::Service()\n" );
    me = this;

    // set the settings of the _win32 service
#ifdef _WIN32
    ServiceStatusHandle = 0;
    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;
#endif

    // load the configuration

    string port = cfg.getValue ( "network", "socket", "port" );
    dispIp = cfg.getValue ( "network", "socket", "ip" );
    daemonIp = cfg.getValue ( "network", "daemon", "ip" );

    daemonPort = cfg.getValue ( "network", "daemon", "tcpport" );
    dmnSitekey = cfg.getValue ( "network", "daemon", "sitekey" );

    icon = cfg.getValue ( "run", "feedback", "icon" );
    runMode = cfg.getValue ( "run", "feedback", "display" );

    LOG ( "\nDaemon found at:%s:%5", daemonIp.c_str(), daemonPort.c_str() );
    DISPATCHER_PORT = atoi ( port.c_str() );
    LOG ( "\nStarting on %d\n" , DISPATCHER_PORT );
}

Service::~Service()
{
    LOG ( "Leaving." );
}

/**
 * Adds a thread to this service
 */
void Service::addThread ( ThreadFunPtr f )
{
    LOG ( "Service::addThread()\n" );
    _threads.push_back ( new Thread ( f ) );
}

Service* Service::getMe()
{
    return me;
}

void Service::pinged()
{
    pingCounter = 0;
}

void Service::notPinged()
{
    pingCounter ++;
}

/**
 * Sends a register message to the daemon
 */
bool Service::registerToDaemon()
{
    stringstream ss;
    ss << "DSP_INIT(tcp:" << dispIp << ":" << DISPATCHER_PORT << ":" << dmnSitekey << ")";
    string dmnReply = sendToDaemon ( ss.str() );
    LOG ( "From daemon:%s", dmnReply.c_str() );
    string replCode = CommandUtils::consume ( dmnReply, '#' );
    if ( replCode == "DSP_ERR" )
    {
        string rsnError = CommandUtils::consume ( dmnReply, ':' );
        LOG ( "The daemon did not accept us because of: %s\n", rsnError.c_str() );
        return false;
    }
    string dispId = CommandUtils::consume ( dmnReply, ':' );
    string newSitekey = dmnReply;
    // now use the data above, and store the new sitekey for later usage
    dmnSitekey = newSitekey;

    return true;
}

/**
 * Runs the service (ie. starts the threads)
 */
void Service::Run()
{
    LOG ( "Service::Run() - entered\n" );

    // now decide if the IP from the config file can be found on the host we're running on
    bool ifaceFound = false;
#ifdef _WIN32
    char hostName[256];
    gethostname ( hostName, 255 );
    LOG ( "Running on host:%s\n", hostName );
    hostent* hostPtr;
    hostPtr = gethostbyname ( hostName );
    char** pptr = hostPtr->h_addr_list;
    while ( *pptr )
    {
        char cIP[256];
        sprintf ( cIP, "%d.%d.%d.%d", ( unsigned char ) ( * ( *pptr ) ), ( unsigned char ) ( * ( *pptr + 1 ) ), ( unsigned char ) ( * ( *pptr + 2 ) ), ( unsigned char ) ( * ( *pptr + 3 ) ) );
        LOG ( "Found interface: %s\n", cIP );
        if ( inet_addr ( cIP ) == inet_addr ( dispIp.c_str() ) )
        {
            LOG ( " >>> Found inner network:%s\n", cIP );
            ifaceFound = true;
        }
        pptr ++;
    }
#else
    // Get a socket handle.
    int sck = socket ( AF_INET, SOCK_DGRAM, 0 );
    if ( sck < 0 )
    {
        LOG ( "Cannot create a temporary socket" );
        return;
    }

    // Query available interfaces.
    char buf[1024];
    struct ifconf ifc;
    struct ifreq* ifr;

    ifc.ifc_len = sizeof ( buf );
    ifc.ifc_buf = buf;
    if ( ioctl ( sck, SIOCGIFCONF, &ifc ) < 0 )
    {
        LOG ( "Error in ioctl(SIOCGIFCONF)" );
        return;
    }

    ifr         = ifc.ifc_req;
    int nInterfaces = ifc.ifc_len / sizeof ( struct ifreq );
    for ( int i = 0; i < nInterfaces; i++ )
    {
        struct ifreq* item = &ifr[i];
        char tmpIp[128];
        snprintf ( tmpIp, 128, "%s", inet_ntoa ( ( ( struct sockaddr_in* ) &item->ifr_addr )->sin_addr ) );
        if ( !strcmp ( tmpIp, dispIp.c_str() ) )
        {
            ifaceFound = true;
        }
    }
#endif

    if ( !ifaceFound )
    {
        LOG ( "Not found network interface we're supposed to start on" );
#ifdef _WIN32
        ErrorExit ( "Run" );
#else
        exit ( 1 );
#endif
    }

    if ( !registerToDaemon() )
    {
        exit ( 1 );
    }

    // joining the threads
    for ( std::vector<Thread*>::iterator it = _threads.begin(); it != _threads.end(); it++ )
    {
        ( *it )->join();
    }
}

string Service::sendToDaemon ( const std::string& s )
{
    LOG ( "Trying to send [%s] to the daemon\n", s.c_str() );
    try
    {
        // now prepare a message to be sent to the daemon to inform of the existence of a new dispatcher
        boost::asio::io_service iodmn;
        boost::asio::ip::tcp::resolver dmnResolver ( iodmn );
        boost::asio::ip::tcp::resolver::query query ( this->daemonIp, this->daemonPort );
        boost::asio::ip::tcp::resolver::iterator iter = dmnResolver.resolve ( query );
        boost::system::error_code error = boost::asio::error::host_not_found;
        boost::asio::ip::tcp::resolver::iterator end; // End marker.
        boost::asio::ip::tcp::socket regSock ( iodmn );
        while ( iter != end )
        {
            boost::asio::ip::tcp::endpoint endpoint = *iter++;
            regSock.close();
            regSock.connect ( endpoint, error );
        }
        if ( error )
        {
            LOG ( "Cannot connect to the daemon\n" );
            return "DSP_ERR#Cannot connect to the daemon:";
        }
        LOG ( "Connected to the daemon, sending message size\n" );

        boost::asio::streambuf dmnRequest;
        std::ostream strmRequest ( &dmnRequest );

        size_t n = 0;
        // write the request to the output socket

        // and now prepare to receive something from there, reserve 512 bytes in output sequence
        boost::asio::streambuf::mutable_buffers_type bufs = dmnRequest.prepare ( 512 );

        strmRequest.clear();
        // now send the data to the socket
        strmRequest << s;
        n = regSock.send ( dmnRequest.data() );

        // we need to "synchronize" the communication going on between the components, wait 2 seconds
#ifdef _WIN32
        Sleep ( 100 );
#else
        sleep ( 100 );
#endif

        // reserve 512 bytes in output sequence
        bufs = dmnRequest.prepare ( 512 );
        n = regSock.receive ( bufs );
        dmnRequest.commit ( n );

        std::istream is2 ( &dmnRequest );
        std::string sreply2;
        is2 >> sreply2;
        LOG ( "As reply from there: %s\n", sreply2.c_str() );
        regSock.close();
        return sreply2;
    }
    catch ( std::exception& e )
    {
        LOG ( "Exception:%s\n",  e.what() );
        return std::string("DSP_ERR#Exception while sending") + e.what();
    }
}

/**
 * Stops the service, and the threads
 */
void Service::Stop()
{
    LOG ( "Service::Stop()\n" );
    for ( std::vector<Thread*>::iterator it = _threads.begin(); it != _threads.end(); it++ )
    {
        ( *it )->interrupt();
    }
}

#ifdef _WIN32

/**
 * Leaves the application after logging a message
 */
void Service::ErrorExit ( const char* lpszFunction )
{
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();
    FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dw, MAKELANGID ( LANG_NEUTRAL, SUBLANG_DEFAULT ), ( LPTSTR ) &lpMsgBuf, 0, NULL );
    LOG ( "%s failed with error %d: %s\n", lpszFunction, dw, lpMsgBuf );
    if ( dw == 1063 )
    {
        MessageBox ( NULL, "Dispatcher is configured to run as a service.\nPlease don't try to run the Dispatcher from the executable, but from\nControl Panel -> Administrative Tools -> Services\nor change the configuration file dispatcher.xml", "Error", MB_OK );
    }
    LocalFree ( lpMsgBuf );
    ExitProcess ( 1 );
}

/**
 * Starts the service
 */
void Service::Start()
{
    if ( runMode == "service" )
    {
        LOG ( "Service::Start()\n" );
        static SERVICE_TABLE_ENTRY ServiceTable[] = { { C_CHAR ( me->ServiceName ), Main }, { 0 , 0 } };
        int servRes = StartServiceCtrlDispatcher ( ServiceTable );
        if ( !servRes )
        {
            ErrorExit ( "Service::Start" );
            me->LogWindowsEvent ( EVENTLOG_ERROR_TYPE, "Could not start service control dispatcher" );
            me->Stop();
            ExitProcess ( 1 );
        }
    }
    else
    {
        atexit ( AtExit );
        me->Run();
    }
}

void Service::AtExit()
{
    LOG ( "Exiting" );
    me->Stop();
}

/**
 * The main entry procedure of the service
 */
void WINAPI Service::Main ( DWORD, LPTSTR* )
{
    LOG ( "Service::Main()\n" );
    me->ServiceStatusHandle = RegisterServiceCtrlHandler ( C_STR ( me->ServiceName ), ControlHandler );
    if ( !me->ServiceStatusHandle )
    {
        me->LogWindowsEvent ( EVENTLOG_ERROR_TYPE,  "Could not register service control handler" );
    }
    me->UpdateStatus ( SERVICE_RUNNING );
    me->Run();
    me->UpdateStatus ( SERVICE_STOPPED );
}


void Service::LogWindowsEvent ( WORD eventType, const char* eventText )
{
    LOG ( "Service::LogWindowsEvent()\n" );
    HANDLE eventSource;
    eventSource = RegisterEventSource ( 0, C_STR ( ServiceName ) );
    if ( !eventSource )
    {
        ReportEvent ( eventSource, eventType, 0, 0, 0, 1, 0, &eventText, 0 );
        DeregisterEventSource ( eventSource );
    }
}

void Service::UpdateStatus ( DWORD status )
{
    LOG ( "UpdateStatus( %d )\n", status );
    if ( ServiceStatusHandle )
    {
        ServiceStatus.dwCurrentState = status;
        SetServiceStatus ( ServiceStatusHandle, &ServiceStatus );
    }
}

void WINAPI Service::ControlHandler ( DWORD control )
{
    LOG ( "Service::ControlHandler()\n" );
    if ( control == SERVICE_CONTROL_STOP )
    {
        me->UpdateStatus ( SERVICE_STOP_PENDING );
        me->Stop();
        me->UpdateStatus ( SERVICE_STOPPED );
    }
}

#else

void Service::TermSignalHandler ( int )
{
    LOG ( "Service::TermSignalHandler()\n" );
    me->Stop();
    exit ( 0 );
}

void Service::Start()
{
    LOG ( "Service::Start()\n" );
    signal ( SIGTERM, TermSignalHandler );
    me->Run();
}

#endif


