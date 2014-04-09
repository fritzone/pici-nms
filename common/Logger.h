#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>

// the Logger macros
#define LOGFILE(s) Logger::init(s)

#define LOG LOG_INF
#define LOG_INF(s) Logger::getInstance().Log(s, 0, __FILE__, __FUNCTION__, __LINE__);
#define LOG_ERR(s) Logger::getInstance().Log(s, 1, __FILE__, __FUNCTION__, __LINE__);
#define LOG_DBG(s) Logger::getInstance().Log(s, 2, __FILE__, __FUNCTION__, __LINE__);

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
    int Log ( const std::string& msg, int code, const char* file, const char* func, int line ) const;

    /**
     * Destroys the Logger
     */
    int destroy();

    void setDirectory(const char* dir);


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
    mutable std::string logFile;


};

#endif

