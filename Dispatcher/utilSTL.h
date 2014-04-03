#pragma once
#include "base.h"

namespace util
{
	namespace stl
	{
		template <typename T> T stl_pulln(T& container, int n)
		{
			int i = 0;
			T ret;	
			while ( i < n )
			{
				if ( EMPTY(container) ) break;
				ret.push_back ( container.back() );
				container.pop_back();
				i++;
			}
			return ret;
		}
	}
}

