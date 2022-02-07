#if __cplusplus < 202002L
        #error "Included version of mcl/strmanip.h meant for at least C++20.  Do not directly include mcl/cpp20/strmanip.h; use mcl/strmanip.h instead."
#endif

#ifndef MCL_STRING_MANIPULATION_H
#define MCL_STRING_MANIPULATION_H

#include "../typedefs.h"
/* ullint, llint
*/
#include <locale>
/* isgraph
*/
#include <stdexcept>
/* std::domain_error
*/


namespace mcl::strmanip
{
	  /*************/
	 /* CONSTANTS */
	/*************/

	const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	enum Side {
		rhs, lhs
	};




	  /*********/
	 /* TYPES */
	/*********/

//Generates getter func for member `m_<mem>`
#define GETTER(mem) decltype(m_ ## mem) mem() const { return m_ ## mem; }
//Generates *prototype* for setter func of `m_<mem>`
#define SETTER(mem) NumOpt& mem(decltype(m_ ## mem) v) { m_ ## mem = v; return *this; }
	class NumOpt
	{
		unsigned short m_base;
		Side           m_dir;
		Side           m_sign;
		bool           m_fsign;
		unsigned int   m_min_w;
		unsigned int   m_max_w; //Where any value less than m_min_w (or equal, iff m_min_w == 0) is considered infinity
		char           m_exp; //Where '\0' chooses a reasonable default based on the base.  Otherwise, any printable char is allowed.

		// Something about scientific notation...
	public:
		GETTER(base)
		//SETTER(base) nope. not all inputs are valid
		NumOpt& base(unsigned short);
		GETTER(dir)
		SETTER(dir)
		GETTER(sign)
		SETTER(sign)
		GETTER(fsign)
		SETTER(fsign)
		GETTER(min_w)
		SETTER(min_w)
		GETTER(max_w)
		SETTER(max_w)
		GETTER(exp)
		//SETTER(exp)
		NumOpt& exp(char);

		NumOpt(
				unsigned short b = 6,
				Side           d = rhs,
				Side           s = rhs,
				bool           f = false,
				unsigned int   m = 0,
				unsigned int   M = 0,
				char           e = '\0'
			);
	};
//No longer needed.
#undef GETTER
#undef SETTER

	const NumOpt opt_def{
		6, rhs, rhs, 0, 0, 0, '\0'
	};
	const NumOpt opt_trad{
		10, lhs, lhs, 0, 0,0, '\0'
	};


	  /**************/
	 /* PROTOTYPES */
	/**************/



	std::string hexPair(uint8_t);

	std::string NtoS(ullint, NumOpt = opt_def);

	std::string ItoS(llint, NumOpt = opt_def);



	  /***************/
	 /* DEFINITIONS */
	/***************/

	NumOpt& NumOpt::base(unsigned short b)
	{
		if (b < 2)
			throw std::domain_error(
					"[mcl::strmanip::NumOpt::base] Error: Given base is less than 2."
				);
		if (b > 36)
			throw std::domain_error(
					"[mcl::strmanip::NumOpt::base] Error: Given base is greater than 36."
				);
		m_base = b;
		return *this;
	}
	NumOpt& NumOpt::exp(char e)
	{
		if (!e || isgraph(e))
		{
			m_exp = e;
			return *this;
		}
		else
			throw std::domain_error(
					"[mcl::strmanip::NumOpt::exp] Error: exp must be null or a graphical character."
				);
	}

	NumOpt::NumOpt(
			unsigned short b,
			Side           d,
			Side           s,
			bool           f,
			unsigned int   m,
			unsigned int   M,
			char           e
		)
	{
		base(b).dir(d).sign(s).fsign(f).min_w(m).max_w(M).exp(e);
	}





	std::string hexPair(uint8_t b)
	{
		return std::string{{ digits[b & 0xF], digits[b >> 4] }};
	}

	std::string NtoS(ullint n, NumOpt no)
	{
		if (n == 0)
			return "0";

		std::string out = "";

		switch (no.dir())
		{
		case rhs: {
			while (n)
			{
				out += digits[n % no.base()];
				n /= no.base();
			}
		} break;
		case lhs: {
			ullint p = 1;
			while (p < n)
				p *= no.base();
			while (n)
			{
				p /= no.base();
				out += digits[n / p];
				n %= p;
			}
		} break;
		}

		return out;
	}


	std::string ItoS(llint n, NumOpt no)
	{
		char sign[2] = "\0";
		if (n < 0)
		{
			*sign = '-';
			n = -n;
		}
		else if (no.fsign())
			*sign = '+';

		if (no.sign() == rhs)
			return NtoS(n, no) + sign;
		else
			return sign + NtoS(n, no);
	}



	std::string trim(const std::string& s)
	{
		auto i = s.begin(), e = s.end();
		while (i != e && std::isspace(*i))
			++i;
		while (i != e && std::isspace(e[-1]))
			--e;

		return {i, e};
	}

	std::string ensurePrintable(char c, bool escback = 1)
	{
		switch (c)
		{
			case '\\': return escback ? "\\\\" : "\\";
			case '\a': return "\\a";
			case '\b': return "\\b";
			case '\x1B': return "\\e";
			case '\f': return "\\f";
			case '\n': return "\\n";
			case '\r': return "\\r";
			case '\t': return "\\t";
			case '\v': return "\\v";
		}

		if (std::isprint(c))
			return std::string{1, c};
		else
			return std::string{{ '\\', 'x', digits[ c & 15 ], digits[ c >> 4 ] }};
	}

	std::string ensurePrintable(std::string s, bool escback = 1)
	{
		std::string out;
		for (char c : s)
			out += ensurePrintable(c, escback);
		return out;
	}
}

namespace mcl {
	using strmanip::NtoS;
	using strmanip::ItoS;
	using strmanip::hexPair;
	using strmanip::trim;
	using strmanip::ensurePrintable;
}


#endif

