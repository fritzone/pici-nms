#ifndef _PARAMETER_NOT_FOUND_H_
#define _PARAMETER_NOT_FOUND_H_

#include "apidef.h"

#include <exception>
#include <string>

using namespace std;

/**
 * Class representing a "parameter not found" exception
 */
class LIBNMS_API parameter_not_found : public std::exception
{
public:
	/**
	 * Constructor, takes in the name of the parameter that was not found
	 */
	parameter_not_found(const string& _pname) throw() : pname(_pname), fwhat("Parameter not found:")
	{ 
		fwhat += pname;
	}

	/**
	 * Destructor
	 */
	virtual ~parameter_not_found() throw() { }

	/**
	 * What
	 */
	virtual const char* what() const throw() 
	{
		return pname.c_str();
	}

	string pname;
	string fwhat;
};

#endif
