#include "BoolWrapper.h"
#include "BoolImpl.h"
#include "ObjImplMapper.h"

#include "Logger.h"
#include <sstream>


using namespace std;

/**
 * Constructor, creates an Bool holding the 0 vaue
 */
Bool::Bool()
{
    BoolImpl* bimpl = new ( std::nothrow ) BoolImpl();
    if ( NULL == bimpl )
    {
        LOG_ERR ( "Not enough memory to create a new Bool implementation" );
        return;
    }
    ObjImplMapper<Bool, BoolImpl>::mapObjToImpl ( this, bimpl );
}

/**
 * Constructor, creates an Bool with the given value
 */
Bool::Bool ( bool _val )
{
    BoolImpl* bimpl = new ( std::nothrow ) BoolImpl ( _val );
    if ( NULL == bimpl )
    {
        LOG_ERR ( "Not enough memory to create a new Bool implementation" );
        return;
    }
    ObjImplMapper<Bool, BoolImpl>::mapObjToImpl ( this, bimpl );
}

/**
 * Constructor, creates an Bool with the value from the given string
 */
Bool::Bool ( const string& _sval )
{
    BoolImpl* bimpl = new ( std::nothrow ) BoolImpl ( _sval );
    if ( NULL == bimpl )
    {
        LOG_ERR ( "Not enough memory to create a new Bool implementation" );
        return;
    }
    ObjImplMapper<Bool, BoolImpl>::mapObjToImpl ( this, bimpl );
}

/**
 * Destructor
 */
Bool::~Bool()
{
    delete ObjImplMapper<Bool, BoolImpl>::getImpl ( this );
    ObjImplMapper<Bool, BoolImpl>::removeImpl ( this );
}

/**
 * The automatic type casting of the Bool to an Bool value
 */
Bool::operator bool () const
{
    return ObjImplMapper<Bool, BoolImpl>::getImpl ( const_cast<Bool*> ( this ) )->getValue();
}

/**
 * Returns the type of the Bool class as a string.
 */
const string& Bool::type() const
{
    return BoolImpl::TYPESTR_BOOL;
}

/**
 * Returns a string representation of the given number
 */
const string Bool::toString() const
{
    stringstream ss;
    ss << ( ObjImplMapper<Bool, BoolImpl>::getImpl ( const_cast<Bool*> ( this ) ) )->getValue();
    return ss.str();
}

