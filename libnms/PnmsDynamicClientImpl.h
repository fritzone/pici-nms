#ifndef _PNMS_DYNAMIC_CLIENT_IMPL_H_
#define _PNMS_DYNAMIC_CLIENT_IMPL_H_

#include "PnmsGenericClientImpl.h"

#include <string>

/**
 * The implementation class of the dynamic clients
 */
class PnmsDynamicClientImpl : public PnmsGenericClientImpl
{
public:
    /**
     * Constructor
     */
    PnmsDynamicClientImpl ( const std::string& name );

    ~PnmsDynamicClientImpl();
};

#endif
