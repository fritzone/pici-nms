#include "LongWrapper.h"
#include "LongImpl.h"
#include "ObjImplMapper.h"

#include "Logger.h"

#include <sstream>


using namespace std;

/**
 * Constructor, creates an Long holding the 0 vaue
 */
Long::Long()
{
LongImpl* limpl = new(std::nothrow) LongImpl();
	if(NULL == limpl)
	{
		LOG_ERR("Not enough memory to create a new long implementation");
		return;
	}
	ObjImplMapper<Long,LongImpl>::mapObjToImpl(this, limpl);
}

/**
 * Constructor, creates an Long with the given value
 */
Long::Long(long _val)
{
LongImpl* limpl = new(std::nothrow) LongImpl(_val);
	if(NULL == limpl)
	{
		LOG_ERR("Not enough memory to create a new long implementation");
		return;
	}
	ObjImplMapper<Long,LongImpl>::mapObjToImpl(this, limpl);
}

/**
 * Constructor, creates an Long with the value from the given string
 */
Long::Long(const string& _sval)
{
LongImpl* limpl = new(std::nothrow) LongImpl(_sval);
	if(NULL == limpl)
	{
		LOG_ERR("Not enough memory to create a new long implementation");
		return;
	}
	ObjImplMapper<Long,LongImpl>::mapObjToImpl(this, limpl);
}

/**
 * Destructor
 */
Long::~Long()
{
	delete ObjImplMapper<Long,LongImpl>::getImpl(this);
	ObjImplMapper<Long,LongImpl>::removeImpl(this);
}

/**
 * The automatic type casting of the Long to an Long value
 */
Long::operator long () const
{
	return ObjImplMapper<Long,LongImpl>::getImpl(const_cast<Long*>(this))->getValue();
}

/**
 * Returns the type of the Long class as a string.
 */
const string& Long::type() const
{
	return LongImpl::TYPESTR_LONG;
}

/**
 * Returns a string representation of the given number
 */
const string Long::toString() const
{
stringstream ss;
	ss << (ObjImplMapper<Long,LongImpl>::getImpl(const_cast<Long*>(this)))->getValue();
	return ss.str();
}
