#include "utilStrings.h"
#define BEGIN_NAMESPACE(ns) namespace ns {
#define END_NAMESPACE(ns) }

int util::strings::cntch(char* cnt, char ch)
{
	int num = 0;
	while(*cnt != '\0') { if ( *cnt == ch ) num++; ++cnt; }
	return num;
}

long util::strings::tokvalue(char* cnt)
{
	long val = 0;
	while(*cnt != '\0') { val += (long)(int)*cnt;  ++cnt; }
	return val;
}

char* util::strings::ripCtrl(char* ptrContent)
{
	size_t pos = 0, len = strlen(ptrContent);
	char* ptrPlain = new char[len];
	while ( *ptrContent != '\0')
	{
		if ( (int)*ptrContent < 32 ) ptrPlain[pos] = ' ';
		else ptrPlain[pos] = *ptrContent;
		++ptrContent;
		++pos;
	} 
	ptrPlain[pos] = '\0';
	return ptrPlain;
}

int util::strings::find(char* cnt, char ch)
{
	char* pStr = strchr(cnt,ch);
	int pos = 0;
	if (pStr) pos = ( pStr - (char*)cnt ) + 1;
	return pos;
}

inline bool util::strings::getline( std::string& cnt,  std::string& line)
{
	return extractto(cnt,line,"\n"); 
}

bool util::strings::extractto( std::string& cnt,  std::string& result, const char* tok)
{
	size_t postok;
	if ( (postok=cnt.find(tok)) == NPOS ) return false;
	result = cnt.substr(0,postok);
	cnt = cnt.substr(postok+1);
	return true; 
}

bool util::strings::getto( std::string const& cnt,  std::string& result, const char* tok)
{
	size_t postok;
	if ( (postok=cnt.find(tok)) == NPOS ) return false;
	result = cnt.substr(0,postok);//cnt = cnt.substr(postok+1);
	return true; 
}
