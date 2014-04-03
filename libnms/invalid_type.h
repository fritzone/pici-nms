#ifndef _INVALID_TYPE_H_
#define _INVALID_TYPE_H_

#include "apidef.h"

#include <exception>
#include <string>

using namespace std;

class LIBNMS_API invalid_type : public std::exception
{
public:

	/**
	 * Constructor
	 */
	invalid_type(const string& _expected, const string& _found) throw() : expected(_expected), found(_found), fwhat("Invalid type.")
	{ 
		fwhat += " Expected:"; fwhat += expected; fwhat += ". Found:"; fwhat += found;
	}

	/**
	 * Destructor
	 */
	virtual ~invalid_type() throw() { }

	/**
	 * What
	 */
	virtual const char* what() const throw() 
	{
		return fwhat.c_str();
	}

	string expected;
	string found;
	string fwhat;
};

#endif
