#include "DoubleWrapper.h"
#include "DoubleImpl.h"
#include "ObjImplMapper.h"

#include "Logger.h"
#include <sstream>


using namespace std;

/**
 * Constructor, creates an Double holding the 0 vaue
 */
Double::Double()
{
    DoubleImpl* bimpl = new ( std::nothrow ) DoubleImpl();
    if ( NULL == bimpl )
    {
        LOG_ERR ( "Not enough memory to create a new Double implementation" );
        return;
    }
    ObjImplMapper<Double, DoubleImpl>::mapObjToImpl ( this, bimpl );
}

/**
 * Constructor, creates an Double with the given value
 */
Double::Double ( double _val )
{
    DoubleImpl* bimpl = new ( std::nothrow ) DoubleImpl ( _val );
    if ( NULL == bimpl )
    {
        LOG_ERR ( "Not enough memory to create a new Double implementation" );
        return;
    }
    ObjImplMapper<Double, DoubleImpl>::mapObjToImpl ( this, bimpl );
}

/**
 * Constructor, creates an Double with the value from the given string
 */
Double::Double ( const string& _sval )
{
    DoubleImpl* bimpl = new ( std::nothrow ) DoubleImpl ( _sval );
    if ( NULL == bimpl )
    {
        LOG_ERR ( "Not enough memory to create a new Double implementation" );
        return;
    }
    ObjImplMapper<Double, DoubleImpl>::mapObjToImpl ( this, bimpl );
}

/**
 * Destructor
 */
Double::~Double()
{
    delete ObjImplMapper<Double, DoubleImpl>::getImpl ( this );
    ObjImplMapper<Double, DoubleImpl>::removeImpl ( this );
}

/**
 * The automatic type casting of the Double to an Double value
 */
Double::operator double () const
{
    return ObjImplMapper<Double, DoubleImpl>::getImpl ( const_cast<Double*> ( this ) )->getValue();
}

/**
 * Returns the type of the Double class as a string.
 */
const string& Double::type() const
{
    return DoubleImpl::TYPESTR_DOUBLE;
}

/**
 * Returns a string representation of the given number
 */
const string Double::toString() const
{
    stringstream ss;
    ss << ( ObjImplMapper<Double, DoubleImpl>::getImpl ( const_cast<Double*> ( this ) ) )->getValue();
    return ss.str();
}

