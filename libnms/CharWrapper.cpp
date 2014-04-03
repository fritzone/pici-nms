#include "CharWrapper.h"
#include "CharImpl.h"
#include "ObjImplMapper.h"

#include "Logger.h"
#include <sstream>


using namespace std;

/**
 * Constructor, creates an Char holding the 0 vaue
 */
Char::Char()
{
CharImpl* bimpl = new(std::nothrow) CharImpl();
	if(NULL == bimpl)
	{
		LOG_ERR("Not enough memory to create a new Char implementation");
		return;
	}
	ObjImplMapper<Char,CharImpl>::mapObjToImpl(this, bimpl);
}

/**
 * Constructor, creates an Char with the given value
 */
Char::Char(char _val)
{
CharImpl* bimpl = new(std::nothrow) CharImpl(_val);
	if(NULL == bimpl)
	{
		LOG_ERR("Not enough memory to create a new Char implementation");
		return;
	}
	ObjImplMapper<Char,CharImpl>::mapObjToImpl(this, bimpl);
}

/**
 * Constructor, creates an Char with the value from the given string
 */
Char::Char(const string& _sval)
{
CharImpl* bimpl = new(std::nothrow) CharImpl(_sval);
	if(NULL == bimpl)
	{
		LOG_ERR("Not enough memory to create a new Char implementation");
		return;
	}
	ObjImplMapper<Char,CharImpl>::mapObjToImpl(this, bimpl);
}

/**
 * Destructor
 */
Char::~Char()
{
	delete ObjImplMapper<Char,CharImpl>::getImpl(this);
	ObjImplMapper<Char,CharImpl>::removeImpl(this);
}

/**
 * The automatic type casting of the Char to an Char value
 */
Char::operator char () const
{
	return ObjImplMapper<Char,CharImpl>::getImpl(const_cast<Char*>(this))->getValue();
}

/**
 * Returns the type of the Char class as a string.
 */
const string& Char::type() const
{
	return CharImpl::TYPESTR_CHAR;
}

/**
 * Returns a string representation of the given number
 */
const string Char::toString() const
{
stringstream ss;
	ss << (ObjImplMapper<Char,CharImpl>::getImpl(const_cast<Char*>(this)))->getValue();
	return ss.str();
}

