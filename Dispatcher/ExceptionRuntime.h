#pragma once
#include <stdexcept>

#define DEFINE_EXCEPTION(ex) class ex : public ExceptionRuntime { public: ex( std::string msg ); };
#define DECLARE_EXCEPTION(ex) ex::ex( std::string msg ) : ExceptionRuntime( msg ){ }
#define EXCEPTION(type) type( c_format("%s at %s:%d", #type,__FILE__,__LINE__) )

class ExceptionRuntime : public std::runtime_error
{
	public:
		ExceptionRuntime( std::string msg );
};



