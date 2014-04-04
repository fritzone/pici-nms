#ifndef _PNMS_DYNAMIC_SECURE_IMPL_H_
#define _PNMS_DYNAMIC_SECURE_IMPL_H_

#include "PnmsGenericClientImpl.h"

#include <string>

class SecureClientInitializer;

/**
 * The implementation class of the dynamic clients
 */
class PnmsSecureClientImpl : public PnmsGenericClientImpl
{
public:

    /**
     * Constructor
     */
    PnmsSecureClientImpl ( const std::string& name );

    /**
     * Destructor
     */
    ~PnmsSecureClientImpl();

    /**
     * Constructor
     */
    PnmsSecureClientImpl ( const std::string& _name, const std::string& configFileLocation );

    /**
     * Initialized? MUST be used before PnmsGenericClientImpl::isInitialized
     */
    bool initialized() const;

private:

    // the initializer
    SecureClientInitializer* sci;

    // whether we've created the transporter or not
    bool ownsTransporter;
};

#endif

