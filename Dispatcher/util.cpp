#include "util.h"

std::string ciresponse_str ( CI_RESPONSE resp )
{
    switch ( resp )
    {
    case CI_OK:
        return "CI_OK";
    case CI_ERRCANTCONNECT:
        return "CI_ERRCANTCONNECT";
    case CI_ERRLOSTCONNECTION:
        return "CI_ERRLOSTCONNECTION";
    case CI_ERRBADRESPONSE:
        return "CI_ERRBADRESPONSE";
    case CI_ERRNOMEMREMOTE:
        return "CI_ERRNOMEMREMOTE";
    case CI_ERRNOMEMLOCAL:
        return "CI_ERRNOMEMLOCAL";
    default:
        return "CI_RESPONSE::UNKNOWN";
    }
}

