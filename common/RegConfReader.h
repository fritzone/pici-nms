#ifdef WIN32

#ifndef _REG_CONF_READER_H_
#define _REG_CONF_READER_H_

#include <string>

using namespace std;

/**
 * Class to read the settings from the registry for the windows based daemon/dispatcher
 */
class RegConfReader
{
public:

	/**
	 * Returns the location of the configuration file
	 */
	static string getConfigFileLocation(const string& comp);
};

#endif

#endif
