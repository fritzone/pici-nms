#pragma once
#include "base.h"

namespace util
{
namespace strings
{
int cntch ( char* cnt, char ch );
long tokvalue ( char* cnt );
char* ripCtrl ( char* ptrContent );
int find ( char* cnt, char ch );
inline bool getline ( std::string& cnt,  std::string& line );
bool extractto ( std::string& cnt,  std::string& result, const char* tok );
bool getto ( std::string const& cnt,  std::string& result, const char* tok );

}
}
