#include "StringWrapper.h"
#include "StringImpl.h"
#include "ObjImplMapper.h"

#include "Logger.h"

#include <sstream>

using namespace std;

/**
 * Constructor, creates an String holding the empty string
 */
String::String()
{
StringImpl* simpl = new (std::nothrow) StringImpl();
	if(NULL == simpl)
	{
		LOG_ERR("Not enough memory to create a new String implementation");
		return;
	}
	ObjImplMapper<String,StringImpl>::mapObjToImpl(this, simpl);
}

/**
 * Constructor, creates an String with the given value
 */
String::String(const char* _val)
{
StringImpl* simpl = new (std::nothrow) StringImpl(_val);
	if(NULL == simpl)
	{
		LOG_ERR("Not enough memory to create a new String implementation");
		return;
	}
	ObjImplMapper<String,StringImpl>::mapObjToImpl(this, simpl);
}

/**
 * Constructor, creates an String with the value from the given string
 */
String::String(const string& _sval)
{
StringImpl* simpl = new (std::nothrow) StringImpl(_sval);
	if(NULL == simpl)
	{
		LOG_ERR("Not enough memory to create a new String implementation");
		return;
	}
	ObjImplMapper<String,StringImpl>::mapObjToImpl(this, simpl);
}

/**
 * Destructor
 */
String::~String()
{
	delete ObjImplMapper<String,StringImpl>::getImpl(this);
	ObjImplMapper<String,StringImpl>::removeImpl(this);
}

/**
 * The automatic type casting of the String to an String value
 */
const char* String::c_str() const
{
	return ObjImplMapper<String,StringImpl>::getImpl(const_cast<String*>(this))->getValue().c_str();
}

/**
 * Returns the type of the String class as a string.
 */
const string& String::type() const
{
	return StringImpl::TYPESTR_STRING;
}

/**
 * Returns a string representation of the given number
 */
const string String::toString() const
{
stringstream ss;
	ss << (ObjImplMapper<String,StringImpl>::getImpl(const_cast<String*>(this)))->getValue();
	return ss.str();
}

