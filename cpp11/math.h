#if __cplusplus < 201103L
	#error "Included version of mcl/math.h meant for at least C++11.  Do not directly include mcl/cpp11/math.h; use mcl/math.h instead."
#endif

#ifndef MCL_MATH_H
#define MCL_MATH_H

#include <math.h> //INFINITY


namespace mcl
{
	const double log2b[] = {
		-INFINITY, //0
		0,
		1,
		1.58496250072116,
		2,
		2.32192809488736,
		2.58496250072116,
		2.8073549220576,
		3,
		3.16992500144231,
		3.32192809488736,
		3.4594316186373,
		3.58496250072116,
		3.70043971814109,
		3.8073549220576,
		3.90689059560852,
		4,
		4.08746284125034,
		4.16992500144231,
		4.24792751344359,
		4.32192809488736,
		4.39231742277876,
		4.4594316186373,
		4.52356195605701,
		4.58496250072116,
		4.64385618977472,
		4.70043971814109,
		4.75488750216347,
		4.8073549220576,
		4.85798099512757,
		4.90689059560852,
		4.95419631038688,
		5,
		5.04439411935845,
		5.08746284125034,
		5.12928301694497,
		5.16992500144231
	};




	/*
	template <typename T, typename N>
	/Supports:
		        T *= T      N >>= 1
						T = 1       (bool)N
		/
	T pow(T b, N p);
	*/

















	/*
	template <typename T, typename N>
	T pow(T b, N p)
	{
		T out = 1;
		for ( ; p; p >>= 1, b *= b)
			if (p & 1) out *= b;
		return out;
	}
	*/
}



#endif

