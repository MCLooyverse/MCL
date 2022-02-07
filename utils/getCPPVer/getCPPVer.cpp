#include <cstdio>

#define STRIZE(s) #s
#define STRIZE_MAC(m) STRIZE(m)

#ifdef __cplusplus
	#define CPPVERSTR STRIZE_MAC(__cplusplus)
#else
	#define CPPVERSTR "Not defined!"
#endif


int main()
{
	puts("#define __cplusplus " CPPVERSTR);
	return 0;
}
