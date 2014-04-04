#pragma once
#include "base.h"

#define PI 3.1415926
#define DEGTORAD(Deg) ((Deg*PI)/180.0)
#define RADTODEG(Rad) ((180.0*Rad)/PI)

namespace util
{
namespace Math
{
LONG lnround ( LONG arg );
}
}
