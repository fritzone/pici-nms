#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>

using namespace std;

// the Logger macros
#define LOGFILE(s) Logger::init(s)
#define LOG LOG_INF

#ifdef _WIN32
#ifdef _DEBUG
#define LOG_INF(s) Logger::getInstance().Log(s, 0, __FILE__, __FUNCTION__, __LINE__);
#define LOG_ERR(s) Logger::getInstance().Log(s, 1, __FILE__, __FUNCTION__, __LINE__);
#define LOG_DBG(s) Logger::getInstance().Log(s, 2, __FILE__, __FUNCTION__, __LINE__);
#else
#define LOG(s)
#define LOG_INF(s)
#define LOG_ERR(s)
#define LOG_DBG(s)
#endif
#else
#ifdef DEBUG
#define LOG_INF(s) Logger::getInstance().Log(s, 0, __FILE__, __FUNCTION__, __LINE__);
#define LOG_ERR(s) Logger::getInstance().Log(s, 1, __FILE__, __FUNCTION__, __LINE__);
#define LOG_DBG(s) Logger::getInstance().Log(s, 2, __FILE__, __FUNCTION__, __LINE__);
#else
#undef LOG
#define LOG(s)
#define LOG_INF(s)
#define LOG_ERR(s)
#define LOG_DBG(s)
#endif
#endif

/**
 * Class responsible for logging of data.
 * If client does not invoke Logger::init
 * no logging will be performed.
 */
class Logger
{

public:

    /**
     * Creates a new Logger object
     */
    Logger();

    /**
     * Deletes a Logger object
     */
    virtual ~Logger();

    /**
     * Logs the given error message, and the error code.
     */
    int Log ( const string& msg, int code, const char* file, const char* func, int line );

    /**
     * Destroys the Logger
     */
    int destroy();

public:

    /**
     * Initializes the logger tot the  given filename/module name
     */
    static void init ( const char* fn );

    /**
     * Returns the instance of the Logger
     */
    static const Logger& getInstance();

private:

    // the singleton instance of the Logger
    static const Logger& instance;

private:

    // the file which will contain the log messages
    static string logFile;

};

#endif

