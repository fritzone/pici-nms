#include "utilDebug.h"

std::string util::debug::log_time ( std::string fmt )
{
    char tmstr[60];
    time_t t = time ( 0 );
    STRFTIME ( tmstr, C_STR ( fmt ), t );
    return tmstr;
}
