#ifndef MCL_LEFT_TO_RIGHT_SEXIMAL_H
#define MCL_LEFT_TO_RIGHT_SEXIMAL_H

#include <string>
#include <istream>
#include <ostream>


namespace mcl
{
	template <typename N>
	std::string   showNatural(N n, size_t min = 0);
	template <typename N>
	N             readNatural(const std::string& s);
	template <typename N>
	std::ostream& showNatural(N n, std::ostream&, size_t min = 0);
	template <typename N>
	N             readNatural(std::istream&);


	template <typename N, typename Iter>
	N             readNatural(Iter& i, const Iter& e);













	template <typename N>
	std::string showNatural(N n, size_t min)
	{
		std::string out;
		while (n)
		{
			out += '0' + (n % 6);
			n   /= 6;
		}

		if (out.size() < min)
			out.insert(out.back(), min - out.size(), '0');
		return out;
	}

	template <typename N>
	N readNatural(const std::string& s)
	{
		N n = 0, p = 1;
		for (char c : s)
		{
			if (c == ' ' || c == '_')
				continue;
			if ('0' <= c && c <  '6')
			{
				n += (c - '0') * p;
				p *= 6;
				continue;
			}

			throw std::domain_error(
					"[mcl::readNatural] String argument was not a natural number."
				);
		}

		return n;
	}

	template <typename N>
	std::ostream& showNatural(N n, std::ostream& s, size_t min)
	{
		size_t sz = 0;
		while (n)
		{
			s << '0' + (n % 6);
			n /= 6;
			++sz;
		}

		if (sz < min)
			s << std::string{min - sz, '0'};

		return s;
	}

	template <typename N>
	N readNatural(std::istream& s)
	{
		N n = 0, p = 1;
		for (char c; (c = s.peek()) != -1; s.ignore())
		{
			if ('0' <= c && c < '6')
			{
				n += (c - '0') * p;
				p *= 6;
			}
			else
				break;
		}

		return n;
	}

	template <typename N, typename Iter>
	N readNatural(Iter& i, const Iter& e)
	{
		N n = 0, p = 1;
		for ( ; i != e; i++)
		{
			if ('0' <= *i && *i < '6')
			{
				n += (*i - '0') * p;
				p *= 6;
			}
			else
				break;
		}

		return n;
	}
}


#endif

