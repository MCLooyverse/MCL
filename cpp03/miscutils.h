#ifndef MCL_MISCELLANEOUS_UTILITIES_H
#define MCL_MISCELLANEOUS_UTILITIES_H


namespace mcl
{
	int hexval(char c)
	{
		if ('0' <= c && c <= '9')
			return c - '0';
		if ('A' <= c && c <= 'F')
			return c - 'A' + 10;
		if ('a' <= c && c <= 'f')
			return c - 'a' + 10;
		return -1;
	}
}


#endif

