#include "AbstractInitializer.h"

/**
 * Construcotr
 */
AbstractInitializer::AbstractInitializer() : lastErrorCode ( -1 ), initSuccess ( false )
{

}

bool AbstractInitializer::initialized() const
{
    return initSuccess;
}

int AbstractInitializer::getLastErrorCode() const
{
    return lastErrorCode;
}

void AbstractInitializer::setLastErrorCode ( int code )
{
    lastErrorCode = code;
}
