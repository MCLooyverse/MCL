#if __cplusplus < 201103L
	#error "Included version of mcl/strmanip.h meant for at least C++11.  Do not directly include mcl/cpp11/strmanip.h; use mcl/strmanip.h instead."
#endif

#ifndef MCL_STRING_MANIPULATION_H
#define MCL_STRING_MANIPULATION_H

#include <string>
#include <vector>
#include <cassert>
#include <stdexcept>
#include "../typedefs.h"
#include "../math.h"


/**Takes a type for `i` (e.g. `iterator`, `const_iterator const &`),
  *a function name, and variadic extra arguments, and returns a function
	*that takes a start (`i`) and end (`e`) iterator, and whatever other
	*given arguments, and returns the given type of `i`.
	*/
#define TAKE_ITER_PAIR(I, N, ...) \
	std::string::I N ( \
		std::string::I i, \
		const std::string::const_iterator& e __VA_OPT__(,) \
		__VA_ARGS__ \
	)

//Convert earlier functions to do useful things with strings
#define EXTEND_TO_STR(N) \
	size_t N (std::string s) \
	{ int l = 0; while(l < s.size() && N (s[l])) ++l; return l; }


//Convert earlier string functions to use iterators
#define EXTEND_TO_ITER(I, N) \
	TAKE_ITER_PAIR(I, N) \
	{ while (i != e && N (*i)) ++i; return i; }


namespace mcl
{
	  /*************/
	 /**CONSTANTS**/
	/*************/

	//Character Classes
	enum class cc {
		control,
		whitespace,
		punctuation,
		digit,
		uppercase,
		lowercase,
		extended
	};

	constexpr const char generalDigits[] =
		"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";



	     /***************/
	    /***PROTOTYPES**/
	   /******AND******/
	  /****TRIVIAL****/
	 /**DEFINITIONS**/
	/***************/
	bool isCntrl(char);
	bool isSpace(char);
	bool isPunct(char);
	bool isDigit(char);
	bool isUpper(char);
	bool isLower(char);
	bool isExtnd(char);

	bool isPrint(char c) { return !isCntrl(c); }
	bool isAlpha(char c) { return isLower(c) || isUpper(c); }
	bool isAlnum(char c) { return isAlpha(c) || isDigit(c); }


	int getCCSet(char);


	/** These functions return how many (continuous) characters
		* from the start of the string have the applicable class
		*/
	EXTEND_TO_STR(isCntrl)
	EXTEND_TO_STR(isSpace)
	EXTEND_TO_STR(isPunct)
	EXTEND_TO_STR(isDigit)
	EXTEND_TO_STR(isUpper)
	EXTEND_TO_STR(isLower)
	EXTEND_TO_STR(isExtnd)

	EXTEND_TO_STR(isPrint)
	EXTEND_TO_STR(isAlpha)
	EXTEND_TO_STR(isAlnum)



	/** These functions return the first (const_)iterator in [i, e) whose
		* character is not of the given class.
		*/
	EXTEND_TO_ITER(const_iterator, isCntrl)
	EXTEND_TO_ITER(const_iterator, isSpace)
	EXTEND_TO_ITER(const_iterator, isPunct)
	EXTEND_TO_ITER(const_iterator, isDigit)
	EXTEND_TO_ITER(const_iterator, isUpper)
	EXTEND_TO_ITER(const_iterator, isLower)
	EXTEND_TO_ITER(const_iterator, isExtnd)

	EXTEND_TO_ITER(const_iterator, isPrint)
	EXTEND_TO_ITER(const_iterator, isAlpha)
	EXTEND_TO_ITER(const_iterator, isAlnum)


	/** These functions return the first iterator in [i, e) whose
		* character is not of the given class.
		*/
	EXTEND_TO_ITER(iterator, isCntrl)
	EXTEND_TO_ITER(iterator, isSpace)
	EXTEND_TO_ITER(iterator, isPunct)
	EXTEND_TO_ITER(iterator, isDigit)
	EXTEND_TO_ITER(iterator, isUpper)
	EXTEND_TO_ITER(iterator, isLower)
	EXTEND_TO_ITER(iterator, isExtnd)

	EXTEND_TO_ITER(iterator, isPrint)
	EXTEND_TO_ITER(iterator, isAlpha)
	EXTEND_TO_ITER(iterator, isAlnum)


	/** These functions increment `i` while `*i` has the relevant
		* class, and is less than `e`, then return a reference to `i`
		*/
	EXTEND_TO_ITER(iterator&, isCntrl)
	EXTEND_TO_ITER(iterator&, isSpace)
	EXTEND_TO_ITER(iterator&, isPunct)
	EXTEND_TO_ITER(iterator&, isDigit)
	EXTEND_TO_ITER(iterator&, isUpper)
	EXTEND_TO_ITER(iterator&, isLower)
	EXTEND_TO_ITER(iterator&, isExtnd)

	EXTEND_TO_ITER(iterator&, isPrint)
	EXTEND_TO_ITER(iterator&, isAlpha)
	EXTEND_TO_ITER(iterator&, isAlnum)



	size_t find(char, const std::string&);


	//Returns whether it reached the end of input
	bool ignore(std::istream& s);


	char& mkUpper(char& c)
	{ return c += isLower(c) * ('a' - 'A'); }
	char toUpper(char c)
	{ return c + isLower(c) * ('a' - 'A'); }
	char& mkLower(char& c)
	{ return c -= isUpper(c) * ('a' - 'A'); }
	char toLower(char c)
	{ return c - isUpper(c) * ('a' - 'A'); }

	std::string& mkUpper(std::string& s)
	{ for (char& c : s) mkUpper(c); return s; }
	std::string toUpper(const std::string& s)
	{ std::string o = s; return mkUpper(o); }
	std::string& mkLower(std::string& s)
	{ for (char& c : s) mkLower(c); return s; }
	std::string toLower(const std::string& s)
	{ std::string o = s; return mkLower(o); }


	/** Takes a character to a nicely-readable string.
		* `mode` changes how the character is made readable:
		* - 0: If not printable, make into "\\xXX" form
		* - 1: If not printable, try a C(ish) escape code otherwise,
		* 		use "\xXX" form.
		* - 2: If not printable, try a C(ish) escape code, otherwise,
		* 		use "^X" where `X` is a character in [63, 96)
		* - 3: If not printable, use carot form.
		*
		* Examples:
		* - 'a' -> "a"
		* - '^' ->
		* 	+ mode=0,1: "^"
		* 	+ mode=2,3: "\\^"
		* - '\\' ->
		* 	+ mode=0,1,2: "\\\\"
		* 	+ mode=3: "\\"
		* - '\t' ->
		* 	+ mode=0: "\\x09"
		* 	+ mode=1,2: "\\t"
		* 	+ mode=3: "^I"
		* - '\0' ->
		* 	+ mode=0: "\x00"
		* 	+ mode=1,2: "\0" //Treated like '\n', although technically octal
		* 	+ mode=3: "^@"
		* - '\x1B' ->
		* 	+ mode=0: "\\x1B"
		* 	+ mode=1,2: "\\e"
		* 	+ mode=3: "^["
		* - '\016' ->
		* 	+ mode=0,1: "\\x0E"
		* 	+ mode=2,3: "^N"
		*/
	std::string makePrintable(char c, sint mode = 0);



	//Quickly convert a char into two hex digits representing its ASCII code
	std::string c2hex(char c, bool ltr = 1);


	std::vector<std::string> split(const std::string&, char, bool = 0);




	/*  ['0', '9'] -> [0, 41)
	 *	['A', 'Z'] -> [41, 001)
	 *	['a', 'z'] -> [41, 001)
	 *             -> -1
	 */
	int digitVal(char c)
	{ return c -= isDigit(c) * '0'
		          + isUpper(c) * ('A' - 10)
							+ isLower(c) * ('a' - 10)
							+ !isAlnum(c) * (c + 1); }

	/*	A tiny function to quickly append `n` as a base-10 string
	 *	onto the end of `s`
	 *
	 *	Returns reference to `s`
	 */
	inline std::string& pushB10(std::string&, unsigned int);

	/*	A tiny function to interpret `s` as a base-10 number, and
	 *	return its value.  Note that this function will simply ignore
	 *	non-digits, and throw no error.  `getB10("83 8, \a23\x1B[2;3H")`
	 *	will return 8382323
	 */
	inline unsigned int getB10(const std::string&);

	namespace numopts { //Really an enum
		using type = unsigned int;
		const type
			leftsign = 1,
			lefttoright = 2,
			forcesign = 4,
			//Nothing goes between these.
			forceexpsign = 8,
			cont_ws = 16, //Continue reading through whitespace?
			cont_comma = 32, //Continue reading through comma? (Allow 6,000)
			cont_under = 64, //Continue reading through '_'? (Allow 6_000)
			cont_toobig = 128, //Continue parsing even if input is too large for output?
			erron_toobig = 256, //Throw error if input is too large for output?  Takes precedent over cont_toobig
			erron_unparsable = 512; //Throw error if input contains non-digit, non-ignorable?

		const type //Defaults
			StoNdef = lefttoright | cont_under | cont_toobig,
			StoIdef = lefttoright | cont_under | cont_toobig,
			StoRdef = lefttoright | cont_under | cont_toobig,
			NtoSdef = lefttoright,
			ItoSdef = lefttoright,
			RtoSdef = lefttoright;
	}


	template <typename N>
	N StoN(
		std::string::const_iterator& i,
		const std::string::const_iterator& e,
		const numopts::type opt = numopts::StoNdef,
		unsigned short int b = 6
	);
	template <typename N>
	N StoN(
		const std::string& s,
		size_t* read = 0, //If not null, store number of read chars at given addr
		const numopts::type opt = numopts::StoNdef,
		unsigned short int b = 6  //Input base.  2 <= |b| < 37. b < 0 indicates
															//right-to-left notation, e.g. the widely-used
															//decimal system would be `-10`
	){auto i=s.begin();N o=StoN<N>(i,s.end(),b,opt);if(read)*read+=i-s.begin();return o;}
	template <typename N>
	N StoN(
		std::istream& s,
		const numopts::type opt = numopts::StoNdef,
		unsigned short int b = 6
	);

	template <typename I>
	I StoI(
		std::string::const_iterator& i,
		const std::string::const_iterator& e,
		const numopts::type opt = numopts::StoIdef,
		unsigned short int b = 6
	);
	template <typename I>
	I StoI(
		const std::string& s,
		int& last,
		size_t* read = 0,
		const numopts::type opt = numopts::StoIdef,
		unsigned short int b = 6
	){auto i=s.begin();I o=StoI<I>(i,s.end(),b,opt);if(read)*read+=i-s.begin();return o;}
	template <typename I>
	I StoI(
		std::istream& s,
		const numopts::type opt = numopts::StoIdef,
		unsigned short int b = 6
	);

	template <typename R>
	R StoR(
		std::string::const_iterator& i,
		const std::string::const_iterator& e,
		const numopts::type opt = numopts::StoRdef,
		unsigned short int b = 6
	);
	template <typename R>
	R StoR(
		const std::string& s,
		size_t* read = 0,
		const numopts::type opt = numopts::StoRdef,
		unsigned short int b = 6
	){auto i=s.begin();R o=StoR<R>(i,s.end(),b,opt);if(read)*read+=i-s.begin();return o;}
	template <typename R>
	R StoR(
		std::istream& s,
		const numopts::type opt = numopts::StoRdef,
		unsigned short int b = 6
	);

	template <typename N>
	std::string NtoS(
		N n,
		const numopts::type opt = numopts::NtoSdef,
		size_t minwidth = 0,
		unsigned short int b = 6
	);

	template <typename I>
	std::string ItoS(
		I i,
		const numopts::type opt = numopts::ItoSdef,
		size_t minwidth = 0,
		unsigned short int b = 6
	);

	template <typename R>
	std::string RtoS(
		//Currently writes in decimal form with `frac` fractional digits if
		//`expwidth` is not set.  If `expwidth` is non-zero, will write in
		//scientific notation with `frac` fractional digits in the mantissa.
		//If `expwidth` is positive, the exponent is padded with 0s to be at least
		//`expwidth` wide (excluding a sign), else it's as wide as necessary.
		R r,
		const numopts::type opt = numopts::RtoSdef,
		size_t frac = 4,
		int expwidth = -1,
		char expchar = 'E',
		unsigned short int b = 6
	);





	  /***************/
	 /**DEFINITIONS**/
	/***************/
	bool isCntrl(char c)
	{ return 0 <= c && c < ' ' || c == 0x7F; }
	bool isSpace(char c)
	{
		return c == ' '
			  || c == '\t'
			  || c == '\r'
			  || c == '\n'
			  || c == '\v'
			  || c == '\f';
	}
	bool isPunct(char c)
	{
		return '!' <= c && c < '0'
			  || ':' <= c && c < 'A'
				|| '[' <= c && c < 'a'
				|| '{' <= c && c < 0x7F;
	}
	bool isDigit(char c)
	{ return '0' <= c && c < ':'; }
	bool isUpper(char c)
	{ return 'A' <= c && c < '['; }
	bool isLower(char c)
	{ return 'a' <= c && c < '{'; }
	bool isExtnd(char c)
	{ return 0x80 <= (int)c; }

	int getCCSet(char c)
	{
		return isCntrl(c) * (int)cc::control
			   | isSpace(c) * (int)cc::whitespace
			   | isPunct(c) * (int)cc::punctuation
			   | isDigit(c) * (int)cc::digit
			   | isUpper(c) * (int)cc::uppercase
			   | isLower(c) * (int)cc::lowercase
			   | isExtnd(c) * (int)cc::extended;
	}


	size_t find(char c, const std::string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
			if (c == s[i]) return i;
		return s.size();
	}


	bool ignore(std::istream& s)
	{
		while (isSpace(s.peek()) && !s.eof())
			s.ignore();
		return s.eof();
	}

	std::string makePrintable(char c, sint mode)
	{
		if (c == '\\' && mode < 3)
			return "\\\\";
		if (c == '^' && mode > 1)
			return "\\^";
		if (isPrint(c))
			return std::string(1, c);

		switch (mode)
		{
		case 1:
		case 2:
			switch (c)
			{
			case '\a': return "\\a";
			case '\b': return "\\b";
			case '\t': return "\\t";
			case '\n': return "\\n";
			case '\v': return "\\v";
			case '\f': return "\\f";
			case '\r': return "\\r";
			case '\x1B': return "\\e";
			}
		}
		switch (mode)
		{
		case 0:
		case 1:
			return "\\x" + c2hex(c);
		case 2:
		case 3:
			return std::string({'^', c ^ 0x40});
		}


		return std::string(1, c);
	}



	std::string c2hex(char c, bool ltr)
	{
		if (ltr)
			return std::string(
					{ generalDigits[c & 0xF], generalDigits[c >> 4] }
				);
		else
			return std::string(
					{ generalDigits[c >> 4], generalDigits[c & 0xF] }
				);
	}




	std::vector<std::string> split(const std::string& s, char d, bool keep)
	{
		std::vector<std::string> out = {""};
		for (auto c : s)
		{
			if (c != d || keep)
				out.back() += c;
			if (c == d)
				out.push_back("");
		}
		return out;
	}



	inline std::string& pushB10(std::string& s, unsigned int n)
	{
		int p = 1;
		while (p <= n)
			p *= 10;
		while (p /= 10, p)
		{
			s += '0' + (n / p);
			n %= p;
		}
		return s;
	}
	inline unsigned int getB10(const std::string& s)
	{
		unsigned int out = 0;
		for (char c : s)
		{
			c -= '0';
			if (0 <= c && c < 10)
				(out *= 10) += c;
		}
		return out;
	}



	template <typename N>
	N StoN(
		std::string::const_iterator& i,
		const std::string::const_iterator& e,
		const numopts::type opt,
		short int b
	)
	{
		if (b < 2)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ +
				"] Base cannot be less than 2."
			);
		}
		if (b > 36)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ +
				"] Base cannot be greater than 36."
			);
		}

		if (i == e)
			return 0;


		N out = 0, place = 1;
		for (int val; i != e; i++)
		{
			val = digitVal(*i);
			if (val < 0)
			{
				if ( opt & numopts::cont_ws && isSpace(*i)
					|| opt & numopts::cont_comma && *i == ','
					|| opt & numopts::cont_under && *i == '_'
				) continue;

				if (opt & numopts::erron_unparsable)
					throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + *i + "'");
				return out;
			}
			if (val < b)
			{
				if (opt & numopts::lefttoright)
					out += val * place, place *= b;
				else
					(out *= b) += val;
			}
			else
			{
				if (opt & numopts::erron_unparsable)
					throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + *i + "'");
				return out;
			}
		}

		return out;
	}
	template <typename N>
	N StoN(
		std::istream& s,
		const numopts::type opt,
		unsigned short int b
	)
	{
		if (b < 2)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ + "] Base cannot be less than 2."
			);
		}
		if (b > 36)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ + "] Base cannot be greater than 36."
			);
		}

		N out = 0, place = 1;
		char c;
		for (int val; c = s.peek(), s; s.ignore())
		{
			val = digitVal(c);
			if (val < 0)
			{
				if ( opt & numopts::cont_ws && isSpace(c)
					|| opt & numopts::cont_comma && c == ','
					|| opt & numopts::cont_under && c == '_'
				) continue;

				if (opt & numopts::erron_unparsable)
					throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + c + "'");
				break;
			}
			if (val < b)
			{
				if (opt & numopts::lefttoright)
					out += val * place, place *= b;
				else
					(out *= b) += val;
			}
			else
			{
				if (opt & numopts::erron_unparsable)
					throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + c + "'");
				break;
			}
		}

		return out;
	}


	template <typename I>
	I StoI(
		std::string::const_iterator& i,
		const std::string::const_iterator& e,
		const numopts::type opt,
		unsigned short int b
	)
	{
		if (b < 2)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ +
				"] Base cannot be less than 2."
			);
		}
		if (b > 36)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ +
				"] Base cannot be greater than 36."
			);
		}

		if (i == e)
			return 0;


		bool neg = 0;
		I out = 0, place = 1;
		if (opt & numopts::leftsign)
		{
			if (*i == '+')
			{ ++i; }
			else if (*i == '-')
			{ neg = 1; ++i; }
		}

		for (int val; i != e; i++)
		{
			if (!(opt & numopts::leftsign))
			{
				if (*i == '+')
				{ ++i; break; }
				else if (*i == '-')
				{ neg = 1; ++i; break; }
			}

			val = digitVal(*i);
			if (val < 0)
			{
				if ( opt & numopts::cont_ws && isSpace(*i)
					|| opt & numopts::cont_comma && *i == ','
					|| opt & numopts::cont_under && *i == '_'
				) continue;

				if (opt & numopts::erron_unparsable)
					throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + *i + "'");
				break;
			}
			if (val < b)
			{
				if (opt & numopts::lefttoright)
					out += val * place, place *= b;
				else
					(out *= b) += val;
			}
			else
			{
				if (opt & numopts::erron_unparsable)
					throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + *i + "'");
				break;
			}
		}

		return (neg?-out:out);
	}
	template <typename I>
	I StoI(
		std::istream& s,
		const numopts::type opt,
		unsigned short int b
	)
	{
		if (b < 2)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ +
				"] Base cannot be less than 2."
			);
		}
		if (b > 36)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ +
				"] Base cannot be greater than 36."
			);
		}

		bool neg = 0;
		I out = 0, place = 1;
		char c = s.peek();

		if (!s)
			return 0;

		if (opt & numopts::leftsign)
		{
			if (c == '+')
			{ s.ignore(); }
			else if (c == '-')
			{ neg = 1; s.ignore(); }
		}

		for (int val; s.get(c); )
		{
			if (!(opt & numopts::leftsign))
			{
				if (c == '+')
				{ break; }
				else if (c == '-')
				{ neg = 1; break; }
			}

			val = digitVal(c);
			if (val < 0)
			{
				if ( opt & numopts::cont_ws && isSpace(c)
					|| opt & numopts::cont_comma && c == ','
					|| opt & numopts::cont_under && c == '_'
				) continue;

				if (opt & numopts::erron_unparsable)
					throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + c + "'");
				break;
			}
			if (val < b)
			{
				if (opt & numopts::lefttoright)
					out += val * place, place *= b;
				else
					(out *= b) += val;
			}
			else
			{
				if (opt & numopts::erron_unparsable)
					throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + c + "'");
				break;
			}
		}

		return (neg?-out:out);
	}

	template <typename R>
	R StoR(
		std::string::const_iterator& i,
		const std::string::const_iterator& e,
		unsigned int opt,
		unsigned short int b
	)
	{
		if (b < 2)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ +
				"] Base cannot be less than 2."
			);
		}
		if (b > 36)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ +
				"] Base cannot be greater than 36."
			);
		}

		const R binv = 1.0 / (R)(b < 0 ? -b : b);
		char expChar = b < 15 ? 'E' : 0;

		if (i == e)
			return 0;


		R out = 0, place = 1, exp = 1;
		bool neg = 0, hitpoint = 0;
		if (opt & numopts::leftsign)
		{
			if (*i == '+')
			{ ++i; }
			else if (*i == '-')
			{ neg = 1; ++i; }
		}

		for (int val, state = 0;
				 i != e && state >= 0;
				 i++)
		{
			switch (state)
			{
			case 0:
				if (!hitpoint && *i == '.')
				{
					hitpoint = 1;
					if (opt & numopts::lefttoright)
					{
						out /= place;
						place = 1;
					}
					else
						state = 1;
					continue;
				}
				else if (expChar && toUpper(*i) == expChar)
				{
					state = 2;
					continue;
				}
				else if (!(opt & numopts::leftsign) && (*i == '+' || *i == '-'))
				{
					if (*i == '-')
						neg = 1;
					if (++i != e && expChar && toUpper(*i) == expChar)
						state = 2;
					else
						state = -1;

					continue;
				}

				val = digitVal(*i);
				if (val < 0)
				{
					if ( opt & numopts::cont_ws && isSpace(*i)
						|| opt & numopts::cont_comma && *i == ','
						|| opt & numopts::cont_under && *i == '_'
					) continue;

					if (opt & numopts::erron_unparsable)
						throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + *i + "'");

					state = -1;
					continue;
				}
				if (val < b)
				{
					if (opt & numopts::lefttoright)
						out += val * place, place *= b;
					else
						(out *= b) += val;
					break;
				}

				if (opt & numopts::erron_unparsable)
					throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + *i + "'");
				state = -1;
				break;

			case 1: //Only rtl can get here
				if (expChar && toUpper(*i) == expChar)
				{
					state = 2;
					continue;
				}
				else if (!(opt & numopts::leftsign) && (*i == '+' || *i == '-'))
				{
					if (*i == '-')
						neg = 1;
					if (++i != e && expChar && toUpper(*i) == expChar)
						state = 2;
					else
						state = -1;

					continue;
				}

				val = digitVal(*i);
				if (val < 0)
				{
					if ( opt & numopts::cont_ws && isSpace(*i)
						|| opt & numopts::cont_comma && *i == ','
						|| opt & numopts::cont_under && *i == '_'
					) continue;

					if (opt & numopts::erron_unparsable)
						throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + *i + "'");
					state = -1;
					continue;
				}
				if (val < b)
					out += (place *= binv) * val;
				else
				{
					if (opt & numopts::erron_unparsable)
						throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + *i + "'");
					state = -1;
				}
				break;

			case 2: {
				int pow = StoI<int>(i, e, opt, b);
				if (pow < 0)
				{
					pow = -pow;
					place = binv;
				}
				else
					place = b;

				for ( ; pow; pow >>= 1, place *= place)
				{
					if (pow & 1)
						exp *= place;
				}

				state = -1;

			} break;

			}
		}

		return (neg ? -out : out) * exp;
	}
	template <typename R>
	R StoR(
		std::istream& s,
		const numopts::type opt,
		unsigned short int b
	)
	{
		if (b < 2)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ +
				"] Base cannot be less than 2."
			);
		}
		if (b > 36)
		{
			throw std::invalid_argument(
				std::string("[") + __func__ +
				"] Base cannot be greater than 36."
			);
		}

		const R binv = 1.0 / (R)b;
		char expChar = b < 15 ? 'E' : 0;

		R out = 0, place = 1, exp = 1;
		bool neg = 0, hitpoint = 0;
		char c = s.peek();

		if (!s)
			return 0;

		if (opt & numopts::leftsign)
		{
			if (c == '+')
			{ s.ignore(); }
			else if (c == '-')
			{ neg = 1; s.ignore(); }
		}

		for (int val, state = 0;
				 state >= 0 && s.get(c);
				 )
		{
			switch (state)
			{
			case 0:
				if (!hitpoint && c == '.')
				{
					hitpoint = 1;
					if (opt & numopts::lefttoright)
					{
						out /= place;
						place = 1;
					}
					else
						state = 1;
					continue;
				}
				else if (expChar && toUpper(c) == expChar)
				{
					state = 2;
					continue;
				}
				else if (!(opt & numopts::leftsign) && (c == '+' || c == '-'))
				{
					if (c == '-')
						neg = 1;
					if (expChar && toUpper(s.peek()) == expChar && s.ignore())
						state = 2;
					else
						state = -1;

					continue;
				}

				val = digitVal(c);
				if (val < 0)
				{
					if ( opt & numopts::cont_ws && isSpace(c)
						|| opt & numopts::cont_comma && c == ','
						|| opt & numopts::cont_under && c == '_'
					) continue;

					if (opt & numopts::erron_unparsable)
						throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + c + "'");

					state = -1;
					continue;
				}
				if (val < b)
				{
					if (opt & numopts::lefttoright)
						out += val * place, place *= b;
					else
						(out *= b) += val;
					break;
				}

				if (opt & numopts::erron_unparsable)
					throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + c + "'");
				state = -1;
				break;

			case 1: //Only rtl can get here
				if (expChar && toUpper(c) == expChar)
				{
					state = 2;
					continue;
				}
				else if (!(opt & numopts::leftsign) && (c == '+' || c == '-'))
				{
					if (c == '-')
						neg = 1;
					if (expChar && toUpper(s.peek()) == expChar && s.ignore())
						state = 2;
					else
						state = -1;

					continue;
				}

				val = digitVal(c);
				if (val < 0)
				{
					if ( opt & numopts::cont_ws && isSpace(c)
						|| opt & numopts::cont_comma && c == ','
						|| opt & numopts::cont_under && c == '_'
					) continue;

					if (opt & numopts::erron_unparsable)
						throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + c + "'");
					state = -1;
					continue;
				}
				if (val < b)
					out += (place *= binv) * val;
				else
				{
					if (opt & numopts::erron_unparsable)
						throw std::domain_error(
							std::string("[") + __func__ +
							"] Invalid character '" + c + "'");
					state = -1;
				}
				break;

			case 2: {
				int pow = StoI<int>(s, opt, b);
				if (pow < 0)
				{
					pow = -pow;
					place = binv;
				}
				else
					place = b;

				for ( ; pow; pow >>= 1, place *= place)
				{
					if (pow & 1)
						exp *= place;
				}

				state = -1;

			} break;

			}
		}

		return (neg ? -out : out) * exp;
	}




	template <typename N>
	std::string NtoS(
		N n,
		const numopts::type opt,
		size_t minwidth,
		unsigned short int b
	)
	{
		if (b < 2 || b > 36)
			throw std::invalid_argument(
				std::string("[") + __func__ + "] Base must be in [2, 36]."
			);


		if (!n)
			return "0";

		std::string out("");

		if (opt & numopts::lefttoright)
		{
			while (n)
			{
				out += generalDigits[n % b];
				n /= b;
			}

			if (minwidth > out.size())
				out.append(minwidth - out.size(), '0');
		}
		else
		{
			N p = 1;
			while (p <= n)
				p *= b;

			while (p > 1)
			{
				p /= b;
				out += generalDigits[n / p];
				n %= p;
			}

			if (minwidth > out.size())
				out.insert(0, minwidth - out.size(), '0');
		}

		return out;
	}

	template <typename I>
	std::string ItoS(
		I i,
		const numopts::type opt,
		size_t minwidth,
		unsigned short int b
	)
	{
		if (b < 2 || b > 36)
			throw std::invalid_argument(
				std::string("[") + __func__ + "] Base must be in [2, 36]."
			);

		char sign = '-' * (i < 0) + '+' * (i >= 0 && opt & numopts::forcesign);
		std::string out(sign && opt & numopts::leftsign, sign);
		if (sign == '-')
			i = -i;

		out += NtoS(i, opt, minwidth, b);

		if (sign)
			out += sign;

		return out;
	}
	template <typename R>
	std::string RtoS(
		R r,
		const numopts::type opt,
		size_t frac,
		int expwidth,
		char expchar,
		unsigned short int b
	)
	{
		if (b < 2 || b > 36)
			throw std::invalid_argument(
				std::string("[") + __func__ + "] Base must be in [2, 36]."
			);

		char sign = '-' * (r < 0) + '+' * (r >= 0 && opt & numopts::forcesign);
		std::string out(sign && opt & numopts::leftsign, sign);
		if (sign == '-')
			r = -r;


		if (expwidth < 0)
		{
			unsigned int n = r * pow(b, frac);
			while (frac && n % b == 0)
			{
				n /= b;
				--frac;
			}
			out += NtoS((unsigned int)(r * pow(b, frac)), opt, frac+1, b);
			if (frac)
				out.insert(opt & numopts::lefttoright ? frac : out.size() - frac, 1, '.');
			if (sign && !(opt & numopts::leftsign))
				out += sign;
		}
		else
		{
			int exp = 0;
			r = frexp(r, &exp);
			//r0 = r1 * 2^exp1
			R fexp = (R)exp / log2b[b];
			exp = fexp;  //⌊exp1 / log_2(b)⌋
			fexp -= exp; //{exp1 / log_2(b)}
			r *= pow(b, fexp);
			while (r >= b)
				r /= b, ++exp;
			while (r < 1)
				r *= b, --exp;

			out += NtoS((unsigned int)(r * pow(b, frac)), opt, frac+1, b);
			if (frac)
				out.insert(opt & numopts::lefttoright ? out.size()-1 : 1, 1, '.');
			if (sign && !(opt & numopts::leftsign))
				out += sign;
			out += expchar;
			out += ItoS(exp, opt | (opt & numopts::forceexpsign) >> 1, expwidth, b);
		}

		return out;
	}
}


//Clean up defs
#undef EXTEND_TO_ITER
#undef EXTEND_TO_STR
#undef TAKE_ITER_PAIR

#endif

