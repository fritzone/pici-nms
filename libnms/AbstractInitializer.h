#ifndef _ABSTRACT_INITIALIZER_H_
#define _ABSTRACT_INITIALIZER_H_

/**
 * Class (interface) responsible for initializing a client. Derivates of this
 * class do the actual work, such as initializing the client as a dynamic client,
 * or a secure client or a trustd client.
 */
class AbstractInitializer
{
public:

    class ErrorCodes
    {
    public:
        static const int INTERNAL_ERROR         = -7;
        static const int TIMEOUT                = -6;
        static const int MALFORMED_RESPONSE     = -4;
        static const int WRONG_NUMBER           = -5;
        static const int NO_RESPONSE            = -3;
        static const int NOT_ENOUGH_MEMORY      = -1;
    };

public:

    /**
     * Constructor
     */
    AbstractInitializer();

    virtual ~AbstractInitializer() {}

    /**
     * Initializes the client
     */
    virtual bool initializeClient() = 0;

    /**
     * Returns true if the initializer succeeded in initializing the client
     */
    bool initialized() const;

    /**
     * Forcefully fails the status of this initializer
     */
    virtual void forceFail()
    {
        initSuccess = false;
    }

    /**
     * Forcefully succeeds the status of the client
     */
    virtual void forceSuccess()
    {
        initSuccess = true;
    }

    /**
     * Returns the last error code
     */
    int getLastErrorCode() const;

    /**
     * Sets the last error to an accepted value
     */
    virtual void setLastErrorCode ( int code );

private:

    // the code of the last error
    int lastErrorCode;

    // true if this transporter object is initialized
    bool initSuccess;

};

#endif
