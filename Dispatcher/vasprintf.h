#pragma once

#if HAVE_VASPRINTF
	#include <stdio.h>
#else
	#include <cstdarg>
	int vasprintf (char **result, const char *format, va_list args);
#endif

