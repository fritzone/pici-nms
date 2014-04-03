#include "IntWrapper.h"
#include "IntImpl.h"
#include "ObjImplMapper.h"

#include "Logger.h"

#include <sstream>


using namespace std;

/**
 * Constructor, creates an integer holding the 0 vaue
 */
Integer::Integer()
{
IntImpl* iimpl = new(std::nothrow) IntImpl();
	if(NULL == iimpl)
	{
		LOG_ERR("Not enough memory to create a new int implementation");
		return;
	}
	ObjImplMapper<Integer,IntImpl>::mapObjToImpl(this, iimpl);
}

/**
 * Constructor, creates an integer with the given value
 */
Integer::Integer(int _val)
{
IntImpl* iimpl = new(std::nothrow) IntImpl(_val);
	if(NULL == iimpl)
	{
		LOG_ERR("Not enough memory to create a new int implementation");
		return;
	}
	ObjImplMapper<Integer,IntImpl>::mapObjToImpl(this, iimpl);
}

/**
 * Constructor, creates an integer with the value from the given string
 */
Integer::Integer(const string& _sval)
{
IntImpl* iimpl = new(std::nothrow) IntImpl(_sval);
	if(NULL == iimpl)
	{
		LOG_ERR("Not enough memory to create a new int implementation");
		return;
	}
	ObjImplMapper<Integer,IntImpl>::mapObjToImpl(this, iimpl);
}

/**
 * Destructor
 */
Integer::~Integer()
{
	delete ObjImplMapper<Integer,IntImpl>::getImpl(this);
	ObjImplMapper<Integer,IntImpl>::removeImpl(this);
}

/**
 * The automatic type casting of the Int to an integer value
 */
Integer::operator int () const
{
	return ObjImplMapper<Integer,IntImpl>::getImpl(const_cast<Integer*>(this))->getValue();
}

/**
 * Returns the type of the Integer class as a string.
 */
const string& Integer::type() const
{
	return IntImpl::TYPESTR_INTEGER;
}

/**
 * Returns a string representation of the given number
 */
const string Integer::toString() const
{
stringstream ss;
	ss << (ObjImplMapper<Integer,IntImpl>::getImpl(const_cast<Integer*>(this)))->getValue();
	return ss.str();
}
