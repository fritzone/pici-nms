#include "utilMath.h"

LONG util::Math::lnround ( LONG arg )
{
    DOUBLE lg = log10 ( ( DOUBLE ) arg ) - 1;
    LONG order =  ceil ( pow ( 10, lg ) );
    return ( arg / order ) * order + order;
}
