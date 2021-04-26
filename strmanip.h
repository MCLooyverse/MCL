#ifndef MCL_STRING_MANIPULATION_H
#define MCL_STRING_MANIPULATION_H

#include <string>
#include "typedefs.h"
#include <vector>
#include <stdexcept>


namespace mcl
{
	namespace strmanip_consts
	{
		constexpr const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		constexpr const char whitespace[] = " \r\n\t";
	}

	enum charClass {
		control,
		whitespace,
		punctuation,
		digit,
		uppercase,
		lowercase,
		extended
	};

	enum smerr {
		invalidBase
	};

	template <typename N> std::string NtoS(N, usint = 10, uint = 0, bool = 0);


	template <typename N> size_t SintoN (
		std::string::const_iterator&,
		const std::string::const_iterator&,
		N&, usint = 10, bool = 0);
	template <typename Z> size_t SintoI (
		std::string::const_iterator&,
		const std::string::const_iterator&,
		Z&, usint = 10, bool = 0);

	template <typename N> N StoN(const std::string&, usint = 10, bool = 0);
	template <typename Z> Z StoI(const std::string&, usint = 10, bool = 0);

	/**
	 * A tiny function to quickly append `n` as a base-10 string
	 * onto the end of `s`
	 * 
	 * Returns reference to `s`
	 */
	inline std::string& pushB10(std::string&, unsigned int);

	/**
	 * A tiny function to interpret `s` as a base-10 number, and
	 * return its value.  Note that this function will simply ignore
	 * non-digits, and throw no error.  `getB10("83 8, \a23\x1B[2;3H")`
	 * will return 8382323
	 */
	inline unsigned int getB10(const std::string&);



	namespace rseximal {
		template <typename N> std::string NtoS(N n, uint m = 0)
		{ return mcl::NtoS(n, 6, m, 1); }

		template <typename N> size_t SintoN (
			std::string::const_iterator& i,
			const std::string::const_iterator& e,
			N& n)
		{ return mcl::SintoN(i, e, n, 6, 1); }
		template <typename Z> size_t SintoI (
			std::string::const_iterator& i,
			const std::string::const_iterator& e,
			Z& z)
		{ return mcl::SintoI(i, e, z, 6, 1); }

		template <typename N> N StoN(const std::string& s)
		{ return mcl::StoN<N>(s, 6, 1); }
		template <typename Z> Z StoI(const std::string& s)
		{ return mcl::StoI<Z>(s, 6, 1); }
	}


	charClass getCClass(char);
	bool isCntrl(char);
	bool isWhite(char);
	bool isPunct(char);
	bool isDigit(char);
	bool isUpper(char);
	bool isLower(char);
	bool isAlpha(char);
	bool isAlnum(char);

	bool isCntrl(const std::string::const_iterator& i) { return isCntrl(*i); }
	bool isWhite(const std::string::const_iterator& i) { return isWhite(*i); }
	bool isPunct(const std::string::const_iterator& i) { return isPunct(*i); }
	bool isDigit(const std::string::const_iterator& i) { return isDigit(*i); }
	bool isUpper(const std::string::const_iterator& i) { return isUpper(*i); }
	bool isLower(const std::string::const_iterator& i) { return isLower(*i); }
	bool isAlpha(const std::string::const_iterator& i) { return isAlpha(*i); }
	bool isAlnum(const std::string::const_iterator& i) { return isAlnum(*i); }
	
	size_t isCntrl(const std::string&);
	size_t isWhite(const std::string&);
	size_t isPunct(const std::string&);
	size_t isDigit(const std::string&);
	size_t isUpper(const std::string&);
	size_t isLower(const std::string&);
	size_t isAlpha(const std::string&);
	size_t isAlnum(const std::string&);


	std::string::const_iterator isCntrl(std::string::const_iterator i, const std::string::const_iterator& e);
	std::string::const_iterator isWhite(std::string::const_iterator i, const std::string::const_iterator& e);
	std::string::const_iterator isPunct(std::string::const_iterator i, const std::string::const_iterator& e);
	std::string::const_iterator isDigit(std::string::const_iterator i, const std::string::const_iterator& e);
	std::string::const_iterator isUpper(std::string::const_iterator i, const std::string::const_iterator& e);
	std::string::const_iterator isLower(std::string::const_iterator i, const std::string::const_iterator& e);
	std::string::const_iterator isAlpha(std::string::const_iterator i, const std::string::const_iterator& e);
	std::string::const_iterator isAlnum(std::string::const_iterator i, const std::string::const_iterator& e);

	std::string::iterator isCntrl(std::string::iterator i, const std::string::const_iterator& e);
	std::string::iterator isWhite(std::string::iterator i, const std::string::const_iterator& e);
	std::string::iterator isPunct(std::string::iterator i, const std::string::const_iterator& e);
	std::string::iterator isDigit(std::string::iterator i, const std::string::const_iterator& e);
	std::string::iterator isUpper(std::string::iterator i, const std::string::const_iterator& e);
	std::string::iterator isLower(std::string::iterator i, const std::string::const_iterator& e);
	std::string::iterator isAlpha(std::string::iterator i, const std::string::const_iterator& e);
	std::string::iterator isAlnum(std::string::iterator i, const std::string::const_iterator& e);

	//Returns true if there exists `c :: std::string`
	//such that `a == b + c` or `a + c == b`,
	//false otherwise
	bool extends(const std::string& a, const std::string& b);
	size_t find(char, const std::string&);


	std::string& trimFront(std::string&);
	std::string trimmedFront(const std::string& s)
	{ auto t = s; return trimFront(t); }
	std::string& trimBack(std::string&);
	std::string trimmedBack(const std::string& s)
	{ auto t = s; return trimBack(t); }
	std::string& trim(std::string& s)
	{ trimFront(s); trimBack(s); return s; }
	std::string trimmed(const std::string& s)
	{ auto t = s; return trim(t); }

	std::string& reduceWS(std::string&);
	std::string reducedWS(const std::string& s)
	{ auto a = s; return reduceWS(a); }

	std::string& remove(char c, std::string& s);
	std::string& remove(charClass c, std::string& s);
	/*
	void remove(char c, std::string::iterator i, const std::string::const_iterator& e);
	void remove(charClass c, std::string::iterator i, const std::string::const_iterator& e);
	*/
	std::string removed(char c, std::string s);
	std::string removed(charClass c, std::string s);
	std::string removed(char c, std::string::const_iterator i, const std::string::const_iterator& e);
	std::string removed(charClass c, std::string::const_iterator i, const std::string::const_iterator& e);



	std::vector<std::string> split(std::string s, char delim = '\n', bool include = 0);
	std::vector<std::string> split(std::string s, charClass, bool include = 0);


	std::vector<std::string> tokens(std::string s);



	char toUpper(char);
	char& makeUpper(char& a) { return a = toUpper(a); }
	char toLower(char);
	char& makeLower(char& a) { return a = toLower(a); }
	std::string toUpper(const std::string&);
	std::string& makeUpper(std::string&);
	std::string toLower(const std::string&);
	std::string& makeLower(std::string&);
	std::string toUpper(std::string::const_iterator i, const std::string::const_iterator& e);
	void makeUpper(std::string::iterator i, const std::string::const_iterator& e);
	std::string toLower(std::string::const_iterator i, const std::string::const_iterator& e);
	void makeLower(std::string::iterator i, const std::string::const_iterator& e);



	/**
	 * "  a   B12c " is equivalent to "a b12c" and "\tA\nB12C"
	 */
	bool looseEquivalence(std::string a, std::string b, int lvl = 15);





	  //=============//
	 // DEFINITIONS //
	//=============//

	template <typename N>
	std::string NtoS(N n, usint b, uint m, bool r)
	{
		if (!(2 <= b && b < 37))
			throw std::domain_error("mcl::NtoS: argument `b` must be between 2 and 36");
		using namespace strmanip_consts;

		if (!n)
			return std::string(m + !m, '0');
		
		std::string out{""};
		if (r)
		{
			while (n)
			{
				out += digits[n % b];
				n /= b;
			}

			if (out.length() < m)
				out.append(m - out.length(), '0');
		}
		else
		{
			N p = 1;
			while (p <= n)
				p *= b;

			while (p > 1)
			{
				p /= b;
				out += digits[n / p];
				n %= p;
			}

			if (out.length() < m)
				out.insert(0, m - out.length(), '0');
		}

		return out;		
	}

	template <typename N> N StoN(const std::string& s, usint b, bool r)
	{
		using std::literals::operator""s;
		if (!(2 <= b && b < 37))
			throw std::domain_error("[mcl::StoN] (unsigned short int)b must be between 2 and 36.");
		
		auto reduced = trimmed(s);
		if (isAlnum(reduced) != reduced.size())
			throw std::domain_error("[mcl::StoN] (const std::string&)s must be alpha-numeric once trimmed.");
		N out = 0;
		if (r)
		{
			N p = 1;
			usint v;
			for (char c : reduced)
			{
				v = c - isDigit(c) * '0'
				      - isUpper(c) * ('A' - 10)
							- isLower(c) * ('a' - 10);
				if (v < b)
					out += p * v;
				else
					throw std::domain_error(
						"[mcl::StoN] character '"s + 'c' + "' is not allowed in a base-" + NtoS(b) +
						" number"
					);
			}
		}
		else
		{
			usint v;
			for (char c : reduced)
			{
				v = c - isDigit(c) * '0'
				      - isUpper(c) * ('A' - 10)
							- isLower(c) * ('a' - 10);
				if (v < b)
					(out *= b) += v;
				else
					throw std::domain_error(
						"[mcl::StoN] character '"s + 'c' + "' is not allowed in a base-" + NtoS(b) +
						" number"
					);
			}
		}
		return out;
	}
	template <typename Z> Z StoI(const std::string& s, usint b, bool r)
	{
		using std::literals::operator""s;
		if (!(2 <= b && b < 37))
			throw std::domain_error("[mcl::StoN] (unsigned short int)b must be between 2 and 36.");
		
		auto reduced = trimmed(s);
		if (!reduced.size())
			return 0;

		bool neg = 0;
		if (reduced[0] == '-')
		{
			neg = 1;
			reduced.erase(reduced.begin());
			trimFront(reduced);
		}
		if (isAlnum(reduced) != reduced.size())
			throw std::domain_error("[mcl::StoN] (const std::string&)s must be alpha-numeric once trimmed.");
		Z out = 0;


		if (r)
		{
			Z p = 1;
			usint v;
			for (char c : reduced)
			{
				v = c - isDigit(c) * '0'
				      - isUpper(c) * ('A' - 10)
							- isLower(c) * ('a' - 10);
				if (v < b)
					out += p * v;
				else
					throw std::domain_error(
						"[mcl::StoN] character '"s + 'c' + "' is not allowed in a base-" + NtoS(b) +
						" number"
					);
			}
		}
		else
		{
			usint v;
			for (char c : reduced)
			{
				v = c - isDigit(c) * '0'
				      - isUpper(c) * ('A' - 10)
							- isLower(c) * ('a' - 10);
				if (v < b)
					(out *= b) += v;
				else
					throw std::domain_error(
						"[mcl::StoN] character '"s + 'c' + "' is not allowed in a base-" + NtoS(b) +
						" number"
					);
			}
		}
		if (neg)
			return -out;
		else
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
			if (0 <= c && c <= 9)
				(out *= 10) += c;
		}
		return out;
	}


	charClass getCClass(char c)
	{
		if (isCntrl(c)) return control;
		if (isWhite(c)) return whitespace;
		if (isPunct(c)) return punctuation;
		if (isDigit(c)) return digit;
		if (isUpper(c)) return uppercase;
		if (isLower(c)) return lowercase;
		return extended;
	}
	bool isCntrl(char c) { return 0x00 <= c && c < 0x20 || c == 0x7F; }
	bool isWhite(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
	bool isPunct(char c) { return 0x20 <= c && c < 0x30
			                       || 0x3A <= c && c < 0x41
			                       || 0x5B <= c && c < 0x61
			                       || 0x7B <= c && c < 0x7F; }
	bool isDigit(char c) { return 0x30 <= c && c < 0x3A; }
	bool isUpper(char c) { return 0x41 <= c && c < 0x5B; }
	bool isLower(char c) { return 0x61 <= c && c < 0x7B; }
	bool isAlpha(char c) { return isUpper(c) || isLower(c); }
	bool isAlnum(char c) { return isAlpha(c) || isDigit(c); }
	
	size_t isCntrl(const std::string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
			if (!isCntrl(s[i])) return i;
		return s.size();
	}
	size_t isWhite(const std::string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
			if (!isWhite(s[i])) return i;
		return s.size();
	}
	size_t isPunct(const std::string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
			if (!isPunct(s[i])) return i;
		return s.size();
	}
	size_t isDigit(const std::string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
			if (!isDigit(s[i])) return i;
		return s.size();
	}
	size_t isUpper(const std::string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
			if (!isUpper(s[i])) return i;
		return s.size();
	}
	size_t isLower(const std::string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
			if (!isLower(s[i])) return i;
		return s.size();
	}
	size_t isAlpha(const std::string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
			if (!isAlpha(s[i])) return i;
		return s.size();
	}
	size_t isAlnum(const std::string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
			if (!isAlnum(s[i])) return i;
		return s.size();
	}

	std::string::const_iterator isCntrl(std::string::const_iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isCntrl(i)) ++i;
		return i;
	}
	std::string::const_iterator isWhite(std::string::const_iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isWhite(i)) ++i;
		return i;
	}
	std::string::const_iterator isPunct(std::string::const_iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isPunct(i)) ++i;
		return i;
	}
	std::string::const_iterator isDigit(std::string::const_iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isDigit(i)) ++i;
		return i;
	}
	std::string::const_iterator isUpper(std::string::const_iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isUpper(i)) ++i;
		return i;
	}
	std::string::const_iterator isLower(std::string::const_iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isLower(i)) ++i;
		return i;
	}
	std::string::const_iterator isAlpha(std::string::const_iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isAlpha(i)) ++i;
		return i;
	}
	std::string::const_iterator isAlnum(std::string::const_iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isAlnum(i)) ++i;
		return i;
	}

	std::string::iterator isCntrl(std::string::iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isCntrl(i)) ++i;
		return i;
	}
	std::string::iterator isWhite(std::string::iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isWhite(i)) ++i;
		return i;
	}
	std::string::iterator isPunct(std::string::iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isPunct(i)) ++i;
		return i;
	}
	std::string::iterator isDigit(std::string::iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isDigit(i)) ++i;
		return i;
	}
	std::string::iterator isUpper(std::string::iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isUpper(i)) ++i;
		return i;
	}
	std::string::iterator isLower(std::string::iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isLower(i)) ++i;
		return i;
	}
	std::string::iterator isAlpha(std::string::iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isAlpha(i)) ++i;
		return i;
	}
	std::string::iterator isAlnum(std::string::iterator i, const std::string::const_iterator& e)
	{
		while (i < e && isAlnum(i)) ++i;
		return i;
	}

	bool extends(const std::string& a, const std::string& b)
	{
		for (int i = 0; ; i++)
		{
			if (i == a.size() || i == b.size())
				return 1;
			if (a[i] != b[i])
				return 0;
		}
	}
	size_t find(char c, const std::string& s)
	{
		for (int i = 0; i < s.size(); i++)
			if (s[i] == c) return i;
		return s.size();
	}


	std::string& trimFront(std::string& s)
	{
		return s.erase(0, isWhite(s));
	}
	std::string& trimBack(std::string& s)
	{
		while (isWhite(s.back())) s.pop_back();
		return s;
	}

	std::string& reduceWS(std::string& s)
	{
		for (auto i = s.begin(); i != s.end(); i++)
		{
			auto old = i;
			i = isWhite(i, s.end());
			if (i != old)
				i = s.erase(old, i);
		}
		return s;
	}

	std::string& remove(char c, std::string& s)
	{
		for (auto i = s.begin(); i != s.end(); )
		{
			if (*i == c)
				i = s.erase(i);
			else
				++i;
		}
		return s;
	}
	std::string& remove(charClass c, std::string& s)
	{
		for (auto i = s.begin(); i != s.end(); )
		{
			if (getCClass(*i) == c)
				i = s.erase(i);
			else
				++i;
		}
		return s;
	}
	/*
	void remove(char c, std::string::iterator i, const std::string::const_iterator& e)
	{
		while (i < e)
		{
			if (*i == c)
				i = s.erase(i);
			else
				++i;
		}
	}
	void remove(charClass c, std::string::iterator i, const std::string::const_iterator& e);
	*/
	std::string removed(char c, std::string s)
	{
		std::string out{""};
		for (char ch : s)
		{
			if (ch != c)
				out += ch;
		}
		return out;
	}
	std::string removed(charClass c, std::string s)
	{
		std::string out{""};
		for (char ch : s)
		{
			if (getCClass(ch) != c)
				out += ch;
		}
		return out;
	}
	std::string removed(char c, std::string::const_iterator i, const std::string::const_iterator& e)
	{
		std::string out{""};
		while (i != e)
		{
			if (*i != c)
				out += *i;
			++i;
		}
		return out;
	}
	std::string removed(charClass c, std::string::const_iterator i, const std::string::const_iterator& e)
	{
		std::string out{""};
		while (i != e)
		{
			if (getCClass(*i) != c)
				out += *i;
			++i;
		}
		return out;
	}

	std::vector<std::string> split(std::string s, char delim, bool include)
	{
		std::vector<std::string> out = { "" };
		for (char c : s)
		{
			if (c == delim)
			{
				if (include)
					out.back() += c;
				out.push_back("");
			}
			else
				out.back() += c;
		}
		return out;
	}

	std::vector<std::string> tokens(std::string s)
	{
		return split(reduceWS(trim(s)), ' ');
	}


	
	char toUpper(char a)
	{
		if (isLower(a))
			return a - ('a' - 'A');
		return a;
	}
	char toLower(char a)
	{
		if (isUpper(a))
			return a + ('a' - 'A');
		return a;
	}
	std::string toUpper(const std::string& a)
	{
		std::string out{a};
		return makeUpper(out);
	}
	std::string& makeUpper(std::string& a)
	{
		for (char& c : a) makeUpper(c);
		return a;
	}
	std::string toLower(const std::string& a)
	{
		std::string out{a};
		return makeLower(out);
	}
	std::string& makeLower(std::string& a)
	{
		for (char& c : a) makeLower(c);
		return a;
	}
	std::string toUpper(std::string::const_iterator i, const std::string::const_iterator& e)
	{
		std::string out{""};
		while (i < e) out += toUpper(*i);
		return out;
	}
	void makeUpper(std::string::iterator i, const std::string::const_iterator& e)
	{
		while (i < e) makeUpper(*i);
	}
	std::string toLower(std::string::const_iterator i, const std::string::const_iterator& e)
	{
		std::string out{""};
		while (i < e) out += toLower(*i);
		return out;
	}
	void makeLower(std::string::iterator i, const std::string::const_iterator& e)
	{
		while (i < e) makeUpper(*i);
	}



	bool looseEquivalence(std::string a, std::string b, int lvl)
	{
		if (lvl & 1)
			trim(a), trim(b);
		if (lvl & 2)
			reduceWS(a), reduceWS(b);
		if (lvl & 4)
			makeUpper(a), makeUpper(b);
		if (lvl & 8)
			remove(punctuation, a), remove(punctuation, b);
		return a == b;
	}
}


#endif
