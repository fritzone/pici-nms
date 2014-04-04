#ifndef _COMMAND_UTILS_H_
#define _COMMAND_UTILS_H_

#include <string>

using namespace std;

/**
 * Just a generic purpose class for utilities workingwith commands
 */
class CommandUtils
{
public:
    /**
     * Fetch the leading part of the s till sep
     */
    static string consume ( std::string& s, char sep )
    {
        string resp = "";
        while ( s[0] != sep && s.length() > 1 )
        {
            resp += s[0];
            s = s.substr ( 1 );
        }
        if ( s.length() > 0 )
        {
            s = s.substr ( 1 ); // consumes the separator too
        }
        return resp;
    }
};

#endif
