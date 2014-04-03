#include "Logger.h"

#include <stdio.h>
#include <time.h>

#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

const Logger& Logger::instance = Logger();
string Logger::logFile("");

/**
 * Creates a new logger
 */
Logger::Logger()
{

}

/**
 * Destroys a Logger 
 */
Logger::~Logger()
{

}

/**
 * Logs the given message
 */
int Logger::Log(const string& msg, int code, const char* file, const char* func, int line)
{
	if(logFile.length() == 0)
	{
		return 0;
	}

stringstream ss;

	// 1. prepare the date/time
time_t rawtime;
struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
string dt(asctime (timeinfo) );
	ss << "[" << file << "] (" << func << ":"<< line<< ") " << (code == 0?"INF":code==1?"ERR":code==2?"DBG":"UNK") <<": " << msg << endl;
ofstream of;
	of.open(logFile.c_str(), ios::app);
	of << ss.str();
	of.close();
	return 1;
}

/**
 * Returns the instance of the Logger
 */
const Logger& Logger::getInstance()
{
	return instance;
}

int Logger::destroy()
{
	LOG("Logger destroyed");
	return 1;
}

void Logger::init(const char * fn)
{
	instance.logFile = fn;
	LOG("Logger started");
	getInstance();
}
