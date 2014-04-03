#include "utilConversion.h"
#include "vasprintf.h"

bool util::conversion::strtoi( std::string num, int& outcome )
{
	errno = 0; 
	char *pEnd;
	if ( C_LEN(num) == 0 ) return false;
	outcome = std::strtol(C_STR(num),&pEnd,10);	//DEBUG("STRTOL: num('%s'), outcome('%d'), errno('%d')\n", C_STR(num), outcome, errno );
	return ( errno==0 );
}

bool util::conversion::strtol( std::string num, long& outcome)
{	
	errno = 0; 
	char *pEnd;
	if ( C_LEN(num) == 0 ) return false;
	outcome = std::strtol(C_STR(num),&pEnd,10);	//DEBUG("STRTOL: num('%s'), outcome('%d'), errno('%d')\n", C_STR(num), outcome, errno );
	return ( errno==0 );
}

bool util::conversion::strtoul( std::string num, unsigned long& outcome )
{
	errno = 0; 
	char *pEnd;
	if ( C_LEN(num) == 0 ) return false;
	outcome = std::strtoul( C_STR(num),&pEnd,10);	//DEBUG("STRTOUL: num('%s'), outcome('%d'), errno('%d')\n", C_STR(num), outcome, errno );
	return ( errno==0 );
}

bool util::conversion::strtoh( std::string num, unsigned long& outcome )
{
	errno = 0; 
	char *pEnd;
	if ( C_LEN(num) == 0 ) return false;
	outcome = std::strtoul( C_STR(num),&pEnd,16);	//DEBUG("STRTOH: num('%s'), outcome('%d'), errno('%d')\n", C_STR(num), outcome, errno );
	return ( errno==0 );
}

bool util::conversion::strtod( std::string num, double& outcome )
{
	errno = 0; 
	char *pEnd;
	if ( C_LEN(num) == 0 ) return false;
	outcome = std::strtod(C_STR(num),&pEnd);	//DEBUG("STRTOD: num('%s'), outcome('%f'), errno('%d')\n", C_STR(num), outcome, errno );
	return ( errno==0 );
}

std::string util::conversion::c_format(const char* fmt, ...)
{
	va_list args;
	va_start(args,fmt);
	char *outcome;
	vasprintf(&outcome,fmt,args);
	va_end(args);
	std::string ret( outcome );
	free(outcome);	
	return ret;
}


