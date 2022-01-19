#if __cplusplus < 201103L
	#error "Included version of mcl/typedefs.h meant for at least C++11.  Do not directly include mcl/cpp11/typedefs.h; use mcl/typedefs.h instead."
#endif

#ifndef MCL_TYPEDEFS_H
#define MCL_TYPEDEFS_H


namespace mcl
{
	using sint = short int;
	using usint = unsigned short int;

	using uint = unsigned int;
	using lint = long int;
	using ulint = unsigned long int;
	using llint = long long int;
	using ullint = unsigned long long int;

	using byte = uint8_t;
}


#endif

