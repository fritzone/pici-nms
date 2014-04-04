#ifndef _OBJ_IMPL_MAPPER_H_
#define _OBJ_IMPL_MAPPER_H_

#include <map>
using namespace std;

/**
 * This class holds mappings between objects and their private implementations.
 */
template <typename OBJTYPE, typename IMPLTYPE>
class ObjImplMapper
{
public:

    /**
     * Maps the given object to the given implementation. Used only internally
     */
    static void mapObjToImpl ( OBJTYPE* obj, IMPLTYPE* impl )
    {
        mapping.insert ( make_pair<OBJTYPE*, IMPLTYPE*> ( obj, impl ) );
    }

    /**
     * Returns the implementation for the given object
     */
    static IMPLTYPE* getImpl ( OBJTYPE* obj )
    {
        return mapping.find ( obj )->second;
    }

    static void removeImpl ( OBJTYPE* obj )
    {
        mapping.erase ( obj );
    }


private:
    // the actual map holding the data
    static map<OBJTYPE*, IMPLTYPE*> mapping;
};

// the definition of the map
template <class OBJTYPE, class IMPLTYPE> map<OBJTYPE*, IMPLTYPE*> ObjImplMapper<OBJTYPE, IMPLTYPE>::mapping;

#endif
