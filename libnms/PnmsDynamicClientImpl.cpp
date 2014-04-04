#include "PnmsDynamicClientImpl.h"
#include "Transporter.h"

using namespace std;

/**
 * Constructor
 */
PnmsDynamicClientImpl::PnmsDynamicClientImpl ( const string& name ) : PnmsGenericClientImpl ( name, DYNAMIC_CLIENT )
{

}

PnmsDynamicClientImpl::~PnmsDynamicClientImpl()
{

}
