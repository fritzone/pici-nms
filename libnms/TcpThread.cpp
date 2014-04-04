#include "TcpThread.h"
#include "TransporterImpl.h"
#include "ConnectionThread.h"
#include "Connection.h"
#include "Logger.h"

TcpThread::TcpThread ( TransporterImpl* impl ) : TCPServerThread(), transp ( impl )
{
}
