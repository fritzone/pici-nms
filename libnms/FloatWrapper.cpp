#include "FloatWrapper.h"
#include "FloatImpl.h"
#include "ObjImplMapper.h"

#include "Logger.h"

#include <sstream>


using namespace std;

/**
 * Constructor, creates an Float holding the 0 vaue
 */
Float::Float()
{
FloatImpl* fimpl = new(std::nothrow) FloatImpl();
	if(NULL == fimpl)
	{
		LOG_ERR("Not enough memory to create a new Float implementation");
		return;
	}
	ObjImplMapper<Float,FloatImpl>::mapObjToImpl(this, fimpl);
}

/**
 * Constructor, creates an Float with the given value
 */
Float::Float(float _val)
{
FloatImpl* fimpl = new(std::nothrow) FloatImpl(_val);
	if(NULL == fimpl)
	{
		LOG_ERR("Not enough memory to create a new Float implementation");
		return;
	}
	ObjImplMapper<Float,FloatImpl>::mapObjToImpl(this, fimpl);
}

/**
 * Constructor, creates an Float with the value from the given string
 */
Float::Float(const string& _sval)
{
FloatImpl* fimpl = new(std::nothrow) FloatImpl(_sval);
	if(NULL == fimpl)
	{
		LOG_ERR("Not enough memory to create a new Float implementation");
		return;
	}

	ObjImplMapper<Float,FloatImpl>::mapObjToImpl(this, fimpl);
}

/**
 * Destructor
 */
Float::~Float()
{
	delete ObjImplMapper<Float,FloatImpl>::getImpl(this);
	ObjImplMapper<Float,FloatImpl>::removeImpl(this);
}

/**
 * The automatic type casting of the Float to an Float value
 */
Float::operator float () const
{
	return ObjImplMapper<Float,FloatImpl>::getImpl(const_cast<Float*>(this))->getValue();
}

/**
 * Returns the type of the Float class as a string.
 */
const string& Float::type() const
{
	return FloatImpl::TYPESTR_FLOAT;
}

/**
 * Returns a string representation of the given number
 */
const string Float::toString() const
{
stringstream ss;
	ss << (ObjImplMapper<Float,FloatImpl>::getImpl(const_cast<Float*>(this)))->getValue();
	return ss.str();
}
