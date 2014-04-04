#pragma once

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <clocale>
#include <cerrno>
#include <cmath>

#define DEBUG(...) { (void) printf ( __VA_ARGS__ ); }
#define STRFTIME(str,fmt,tmt) strftime(str,sizeof(str),fmt, localtime(&tmt) )
#define COPY(source,dest) memcpy(&dest,&source,sizeof(source))
#define TYPEID(x) typeid(x).name()
#define FMTARGS(str,fmt) { va_list args; va_start(args,fmt); ULONG len=vsprintf(NULL,fmt,args)+3; char *outcome=new char[len]; vsprintf(outcome,fmt,args); va_end(args); str=outcome; delete outcome; }
#define ALLOC(x) malloc(sizeof(x))
#define ERASE(x) memset(&x,0,sizeof(x))
