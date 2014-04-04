#pragma once

#include "_boostasio.h"
#include "_boostthread.h"
#include "_boostsmartptr.h"

#include "libutil.h"
#include "constants.h"

#include "base.h"

#define TRY try
#define CATCH catch
#define WHILE while

#define _TRACE(...) { (void) printf ( __VA_ARGS__ ); }
#define _LOG(...) logfile << c_format( __VA_ARGS__ ) << flush
#define _LOGFILE(x) std::ofstream logfile(x)

#define LOGFILE _LOGFILE
#define LOG _LOG


#define ASSIGN(x,y) x.assign(y)
#define LOG_TIME(x) C_STR(log_time(x))
#define FMTEXCEPTION(s) c_format("%s: %s in %s:%d.",LOG_TIME("%Y%d%m%H%M%S"),s,__FILE__,__LINE__)
#define EXCEPTIONRUNTIME(s) ExceptionRuntime( FMTEXCEPTION(s) )
#define EXWHAT(ex) ex.what()
#define EXOUT(ex) LOG("%s:%d : %s\n",__FILE__,__LINE__,EXWHAT(ex))
#define EXCEPTION(type) type( c_format("%s at %s:%d", #type,__FILE__,__LINE__) )
#define DEBUGSTR(str) LOG("%s:%d : %s( '%s' )\n",__FILE__,__LINE__,#str,C_STR(str))

using std::cout;
using std::endl;
using std::ofstream;
using std::flush;
using util::conversion::c_format;
using util::conversion::strtoi;
using util::conversion::strtol;
using util::debug::log_time;
using util::strings::extractto;
using util::strings::getto;
using boost::asio::io_service;

typedef unsigned long ULONG;

extern ofstream logfile;
