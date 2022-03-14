#if __cplusplus < 202002L
	#error "Included version of mcl/strmanip.h meant for at least C++20.  Do not directly include mcl/cpp20/strmanip.h; use mcl/strmanip.h instead."
#endif

#ifndef MCL_STRING_MANIPULATION_H
#define MCL_STRING_MANIPULATION_H

#include <string_view>


namespace mcl
{
	std::string& trim(std::string&, const std::string& ws = " \t\r\n");
	std::string& rtrim(std::string&, const std::string& ws = " \t\r\n");
	std::string& ltrim(std::string&, const std::string& ws = " \t\r\n");

	std::string_view trimmed(const std::string&, const std::string& ws = " \t\r\n");
	std::string_view rtrimmed(const std::string&, const std::string& ws = " \t\r\n");
	std::string_view ltrimmed(const std::string&, const std::string& ws = " \t\r\n");








	std::string& trim(std::string& s, const std::string& ws)
	{
		return ltrim(rtrim(s, ws), ws);
	}

	std::string_view trimmed(const std::string& s, const std::string& ws)
	{
		return ltrimmed(rtrimmed(s, ws), ws);
	}


	std::string& rtrim(std::string& s, const std::string& ws)
	{
		while (ws.find(s.back()) != std::string::npos)
			s.pop_back();
		return s;
	}
	std::string& ltrim(std::string& s, const std::string& ws)
	{
		size_t i = 0;
		while (ws.find(s[i]))
			++i;

		return s.erase(0, i);
	}


	std::string_view rtrimmed(const std::string& s, const std::string& ws)
	{
		std::string_view out{s};
		while (ws.find(out.back()) != std::string::npos)
			out.remove_suffix(1);
		return out;
	}
	std::string_view ltrimmed(const std::string& s, const std::string& ws)
	{
		std::string_view out{s};
		while (ws.find(out.front()) != std::string::npos)
			out.remove_prefix(1);
		return out;
	}
}


#endif

