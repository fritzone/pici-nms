#ifndef _PNMS_NETWORK_H_
#define _PNMS_NETWORK_H_

/**
 * Contains code to execute during the very first client connection.
 */
class PnmsNetwork
{
public:

    /**
     * Initializes the library, this is done in a totally transparent way to the user
     * at the creation of the first client.
     */
    static bool initialize();

    // true if the network was initialized, false if not
    static bool initialized;
};

#endif
