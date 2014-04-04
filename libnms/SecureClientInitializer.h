#ifndef _SECURE_CLIENT_INITIALIZER_H_
#define _SECURE_CLIENT_INITIALIZER_H_

#include "AbstractClientInitializer.h"

#include <string>

class ClientConfiguration;

/**
 * Initializes a secure client from a configuration file
 */
class SecureClientInitializer : public AbstractClientInitializer
{
public:

    /**
     * Constructor. Searches for the config file
     */
    SecureClientInitializer();

    /**
     * Destructor
     */
    ~SecureClientInitializer();

    /**
     * Initializer from the given config file
     */
    SecureClientInitializer ( const std::string& configFile );

    /**
     * Initializes the client
     */
    virtual bool initializeClient();

    /**
     * If the client was initialized or not
     */
    bool initialized() const;

private:

    // the configuration object
    ClientConfiguration* cfg;
};

#endif
