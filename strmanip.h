#if __cplusplus >= 202002L
	#include "cpp20/strmanip.h"
#elif __cplusplus >= 201103L
	#include "cpp11/strmanip.h"
#else
	#error "\"mcl/strmanip.h\" does not support this std version"
#endif

