#pragma once
#include "base.h"

typedef unsigned long Hex;

namespace util
{
	namespace conversion
	{
		bool strtoi( std::string num, int& outcome );
		bool strtol( std::string num, long& outcome);
		bool strtoul( std::string num, unsigned long& outcome );
		bool strtoh( std::string num, unsigned long& outcome );
		bool strtod( std::string num, double& outcome );
		std::string c_format(const char* fmt, ...);
	}

}	
