#ifdef WIN32
	#ifndef CYGWIN
		#ifdef LIBNMS_EXPORTS
			#define LIBNMS_API __declspec(dllexport)
		#else
			#define LIBNMS_API __declspec(dllimport)
		#endif
	#else
		#define LIBNMS_API
	#endif
#else
	#define LIBNMS_API
#endif
