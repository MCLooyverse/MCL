#if __cplusplus >= 202002L
	#include "cpp20/args.h"
#elif __cplusplus >= 201103L
	#include "cpp11/args.h"
#else
	#error "\"mcl/args.h\" does not support this std version"
#endif

