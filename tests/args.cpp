#include <mcl/args.h>
#include <mcl/show.h>
#include <mcl/strmanip.h>
#include <iostream>


using std::literals::string_literals::operator""s;




template <typename T, typename... Ts>
concept one_of = (std::same_as<T, Ts> || ...);

template <typename T, typename... Ts>
bool containing(const std::variant<Ts...>& v)
{
	return one_of<T, Ts...> && std::holds_alternative<T>(v);
}

template <typename T, typename... Ts>
	// requires (std::same_as<T, Ts> || ...)
bool operator==(const std::variant<Ts...>& v,
		const T& t)
{
	return containing<T>(v) && std::get<T>(v) == t;
}


std::string dispOpt(char c)
{
	return "-" + mcl::ensurePrintable(c);
}
std::string dispOpt(std::string s)
{
	return "--" + mcl::ensurePrintable(s);
}




enum Opts {
	help, natural,
	string, keyword
};

int main(int argc, char** argv)
{

	auto args{mcl::args::parse<Opts>(
			{
				{ 'h', help    },
				{ 'n', natural },
				{ 's', string  },
				{ 'k', keyword }
			},
			{
				{ "help"s,    help    },
				{ "natural"s, natural },
				{ "string"s,  string  },
				{ "keyword"s, keyword }
			},
			{
				// help; flag -- not mentioned
				{ natural, mcl::args::supplied_parsers::natural<int>() },
				{ string,  mcl::args::supplied_parsers::string },
				{ keyword, mcl::args::supplied_parsers::keyword<int>(
						{ { "primary"s, 0 }, { "secondary"s, 1 }, { "clipboard"s, 2 } })
				}
			},
			argc, argv
		)
	};


	for (auto& a : args)
	{
		if (a.isLit())
			std::cout << "Argument: " << a.as<std::string>() << '\n';
		else if (a.isUnk())
		{
			std::cerr << "Unknown option `"
				<< std::visit([](const auto& o) -> std::string { return dispOpt(o); },
						a.unkOptErr().opt) << '\n';
		}
		else switch (a.opt())
		{
		case help:
			std::cout << "**Help Message**\n";
			break;
		case natural:
			if (a)
				std::cout << "A natural " << mcl::show(a.as<int>()) << '\n';
			else if (a.v)
				std::cerr << "Failed to parse natural\n";
			else
				std::cerr << "Missing argument for natural\n";
			break;
		case string:
			if (a)
				std::cout << "A string \"" << a.as<std::string>() << "\"\n";
			else if (a.v)
				std::cerr << "Failed to parse string\n";
			else
				std::cerr << "Missing argument for string\n";
			break;
		case keyword:
			if (a)
				std::cout << "A keyword \"" << a.as<int>() << "\"\n";
			else if (a.v)
				std::cerr << "Failed to parse keyword\n";
			else
				std::cerr << "Missing argument for keyword\n";
			break;
		}
	}



	for (auto& a : args)
	{
		if (a.isLit())
			a.deleteAs<std::string>();
		else if (a.isUnk())
			a.deleteAs<mcl::args::UnknownOption>();
		else switch (a.opt())
		{
		case help: break;
		case natural:
			a.deleteAs<int>();
			break;
		case string:
			a.deleteAs<std::string>();
			break;
		case keyword:
			a.deleteAs<int>();
			break;
		}
	}

	return 0;
}
