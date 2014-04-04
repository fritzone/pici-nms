#pragma once

#include <string>
#include <iostream>
#include <fstream>

#define NOT(x) x == 0 ? 1:0
#define NONE(x) x == 0
#define STRBOOL(x) x ? "true" : "false"
#define BYTE(x) (unsigned char)(x)
#define _T(x) x
#ifndef WIN32
typedef unsigned long ULONG;
typedef unsigned char BYTE;
typedef long int LONG;
typedef double DOUBLE;
#endif
