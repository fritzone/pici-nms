#pragma once

#include <vector>
#include <list>
#include <map>


#define NPOS std::string::npos	
#define MAP(x,y) std::map<x,y>
#define MAP_E(x,y,z) std::map<x,y,z>
#define MAP_NOTFOUND(x,y) x.find(y) == x.end()
#define PAIR(x,y) std::pair<x,y>
#define LIST(x) std::list<x>
#define QUEUE(x) std::queue<x>
#define VECTOR(x) std::vector<x>
#define C_DATA(x) x.data()
#define C_CHAR(x) &x[0]
#define C_STR(x) x.c_str()
#define C_LEN(x) x.length()
#define STLSIZE(x) x.size()
#define DOTSIZE(x) STLSIZE(x)
#define CLEAR(x) x.clear()
#define SUBSTR(str,a,b) str.substr(a,b)
#define FIND(cnt,it) cnt.find(it)
#define EMPTY(x) x.empty()
