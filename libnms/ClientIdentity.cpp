#include "ClientIdentity.h"

#include <sstream>

using namespace std;

ClientIdentity::ClientIdentity ( string cid )  : identity ( cid )
{
}

ClientIdentity::ClientIdentity ( unsigned long cid )
{
    stringstream ss;
    ss << cid;
    identity = ss.str();
}

const string& ClientIdentity::getIdentityDescriptor() const
{
    return identity;
}
