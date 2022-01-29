#ifndef MCL_ARGUMENT_PARSER_H
#define MCL_ARGUMENT_PARSER_H

#include <filesystem>
#include <functional>
#include <variant>
#include <map>
#include <vector>

/* TODO:
 * Report error on final option with left-out arg
 *
 * `-hn 9` where h is flag and n takes arg ignores
 * n
 */


namespace mcl::args {
	template <typename F, typename R, typename... A>
	concept Functional = requires (F f, A... as) {
		{ f(as...) } -> std::same_as<R>;
	};

	using sv_citer = std::string_view::const_iterator;
	using Reader = std::function<void*(const char*&)>;
	using ShortOrLong = std::variant<char, std::string>;

	enum class NonOpt {
		none, //parse_error,
		unknown_option
	};

	struct ErrorVal
	{
		int index;
		std::string_view arg;
		int around_ind;
	};
	struct UnknownOption
	{
		int index;
		std::string_view arg;
		int around_ind;

		ShortOrLong opt;
	};

	template <typename E>
	struct Arg
	{
		std::variant<E, NonOpt> option;
		bool success;
		void* v;

		bool isLit() const;
		bool isOpt() const;
		bool isUnk() const;

		std::string literal() const;
		std::string& literal();

		ErrorVal parseErr() const;
		
		UnknownOption unkOptErr() const;

		E opt() const;
		E& opt();

		template <typename T>
		T as() const
		{
			if (!isOpt() || !success)
				throw std::logic_error("TODO");
			return *(T*)v;
		}
		template <typename T>
		T& as()
		{
			if (!isOpt() || !success)
				throw std::logic_error("TODO");
			return *(T*)v;
		}

		operator bool() const;
	};

	template <NonOpt e>
	struct RealTypeS;
	template<>
	struct RealTypeS<NonOpt::none> { using type = std::string; };
	// template<>
	// struct RealTypeS<NonOpt::parse_error> { using type = ErrorVal; };
	template<>
	struct RealTypeS<NonOpt::unknown_option> { using type = UnknownOption; };

	template <NonOpt e>
	using RealType = RealTypeS<e>::type;



	template <typename E>
	std::vector<Arg<E>> parse(
		const std::map<ShortOrLong, E>&,
		const std::map<E, Reader>&,
		int, char const * const *,
		bool doubleDashMeansLiterals = 1
	);



	namespace supplied_parsers {
		namespace helper {
			std::string consume_string(const char*& i)
			{
				std::string out{i};
				i += out.size();
				return out;
			}
			std::string& consume_string(const char*& i,
					std::string& out)
			{
				out = i;
				i += out.size();
				return out;
			}
		}

		Reader string = [](const char*& i) -> void* {
			return &helper::consume_string(i,
					*new std::string{}
				);
		};

		//TODO: Fix typename
		template <typename T>
		Reader natural(unsigned short base = 6,
				bool rtl = 0)
		{
			return [=](const char*& i) -> void* {
				auto val = [&base](char c) -> unsigned short {
					if ('0' <= c && c <= '9')
						c -= '0';
					else if ('A' <= c && c <= 'Z')
						c -= 'A' - 10;
					else if ('a' <= c && c <= 'z')
						c -= 'a' - 10;
					else
						c = base;
					return c > base ? base : c;
				};

				auto out = new T{0};
				for (T place = 1; *i; i++)
				{
					int v = val(*i);
					if (v == base)
						return out;

					if (rtl)
						(*out *= base) += v;
					else
					{
						*out += place * v;
						place *= base;
					}
				}

				return out;
			};
		}

		//exist:  1 -> require existance,
		//        0 -> don't care
		//       -1 -> require non-existance
		//Defaults to reading an extant regular file
		Reader filedes(int flags = O_RDONLY, int exist = 1,
				std::filesystem::file_type type =
				std::filesystem::file_type::regular)
		{
			namespace fs = std::filesystem;

			switch (type)
			{
				case fs::file_type::none:
				case fs::file_type::not_found:
					throw std::domain_error("TODO"); //TODO
				default: break;
			}

			if (flags & O_RDONLY == O_RDONLY &&
					exist != 1) //TODO: questionable.
				throw std::domain_error("TODO"); //TODO


			switch (exist)
			{
				case -1: throw 1;
				case 0: throw 1;
				case 1:
					return [=](const char*& i) -> void* {
						fs::path p{helper::consume_string(i)};

						if (type == fs::file_type::unknown && fs::exists(p) ||
								type == fs::status(p).type())
						{
							auto i = new int{open(p.c_str(), flags)};
							if (*i == -1)
								return 0;
						}
						else
							return 0;
					};
				default:
					throw std::domain_error("TODO"); //TODO
			}
		}


		//Return fs::path
		Reader extantPath(std::filesystem::file_type type =
				std::filesystem::file_type::unknown) //unknown means any
		{
			namespace fs = std::filesystem;

			switch (type)
			{
				case fs::file_type::none:
				case fs::file_type::not_found:
					throw std::domain_error("TODO"); //TODO
				default: break;
			}

			return [=](const char*& i) -> void* {
				auto p = new fs::path{helper::consume_string(i)};
				if (type == fs::file_type::unknown && fs::exists(*p) ||
						type == fs::status(*p).type())
					return p;
				delete p;
				return NULL;
			};
		}

		//returns T
		template <typename T>
		Reader keyword(std::map<std::string, T> kws, bool exact = 0)
		{
			if (exact)
				return [=](const char*& i){
			return [=](const char*& i){
				auto start = i, end = i;
				while (*end) ++end;

				for (auto& [k, t] : kws)
		//Return fs::path
		Reader ftypeOrNexist(std::filesystem::file_type type =
				std::filesystem::file_type::unknown) //unknown means any
		{
			namespace fs = std::filesystem;

			switch (type)
			{
				case fs::file_type::none:
				case fs::file_type::not_found:
					throw std::domain_error("TODO"); //TODO
				default: break;
			}

			return [=](const char*& i) -> void* {
				auto p = new fs::path{helper::consume_string(i)};
				if (type == fs::file_type::unknown && fs::exists(*p) ||
						fs::status(*p).type() == fs::file_type::not_found ||
						type == fs::status(*p).type())
					return p;
				delete p;
				return NULL;
			};
		}
	}



	template <typename E>
	bool Arg<E>::isLit() const
	{
		auto p = std::get_if<NonOpt>(&option);
		return p && *p == NonOpt::none;
	}
	template <typename E>
	bool Arg<E>::isOpt() const
	{
		return std::holds_alternative<E>(option);
	}
	template <typename E>
	bool Arg<E>::isUnk() const
	{
		auto p = std::get_if<NonOpt>(&option);
		return p && *p == NonOpt::unknown_option;
	}

	template <typename E>
	std::string Arg<E>::literal() const
	{
		if (!isLit())
			throw std::logic_error("TODO"); //TODO
		return *(std::string*)v;
	}
	template <typename E>
	std::string& Arg<E>::literal()
	{
		if (!isLit())
			throw std::logic_error("TODO"); //TODO
		return *(std::string*)v;
	}

	template <typename E>
	ErrorVal Arg<E>::parseErr() const
	{
		if (!isOpt() || !success)
			throw std::logic_error("TODO"); //TODO
		return *(ErrorVal*)v;
	}
		
	template <typename E>
	UnknownOption Arg<E>::unkOptErr() const
	{
		if (!isUnk())
			throw std::logic_error("TODO"); //TODO
		return *(UnknownOption*)v;
	}

	template <typename E>
	E Arg<E>::opt() const
	{
		if (!isOpt())
			throw std::logic_error("TODO"); //TODO
		return std::get<E>(option);
	}
	template <typename E>
	E& Arg<E>::opt()
	{
		if (!isOpt())
			throw std::logic_error("TODO"); //TODO
		return std::get<E>(option);
	}


	template <typename E>
	Arg<E>::operator bool() const
	{ return success && !isUnk(); }





	template <typename E>
	std::vector<Arg<E>> parse(
		const std::map<ShortOrLong, E>& names,
		const std::map<E, Reader>& ps,
		int argc, char const * const * argv,
		bool doubleDashMeansLiterals
	){
		using Enum = std::variant<E, NonOpt>;

		std::vector<Arg<E>> out;

		auto doParse = [&out, &ps, &argv](E opt,
				int i, const char** pp = 0) -> const char* {
			auto p = pp ? *pp : argv[i];

			if (ps.count(opt))
			{
				out.emplace_back(opt, 1, ps.at(opt)(p));
				if (*p || !out.back().v) //If parser did not eat all input
				{                        //or if parser returned fail
					out.back().success = 0;
					//TODO: Solve potential memory leak
					/*
					if (out.back().v)
						delete out.back().v;
					*/
					out.back().v = new ErrorVal{
						i, argv[i], p - argv[i]
					};
					while (*p)
						++p;
				}
				return p;
			}
			else
			{
				//No parser registered means boolean flag
				//(no argument)
				out.push_back({opt, 1, NULL});
				return ++p;
			}
		};

		auto pushFlag = [&out](E opt){
			// out.emplace_back(opt, 1, NULL);
			out.push_back({opt, 1, NULL});
		};

		auto literalStr = [&out](std::string&& str){
			out.emplace_back(NonOpt::none, 1, new std::string{str});
		};


		//State: Set to enum of previous flag, *if*
		//such a flag was encountered, and takes an
		//argument.
		Enum next = NonOpt::none;

		//State: Forces everything as literal argument
		bool literals = 0;

		//Loop over argv, skipping the program name
		//argv[0]
		for (int k = 1; k < argc; k++)
		{
			//Treating all as literals
			if (literals)
				literalStr(argv[k]);
			else if (next == Enum{NonOpt::none}) //Not impacted by a previous arg
			{
				unsigned short dashes = 0;
				const char* p = argv[k];
				while (*p == '-' && dashes < 2)
				{
					++dashes;
					++p;
				}

				switch (dashes)
				{
				case 0:
					literalStr(argv[k]);
					break;
				case 1:
					while (*p)
					{
						if (!names.count(*p))
						{
							out.emplace_back(
									NonOpt::unknown_option, 0,
									new UnknownOption{
										k, argv[k], p - argv[k],
										*p
									}
								);
						}
						else
						{
							E opt = names.at(*p++);
							if (*p) //If there is more string:
								p = doParse(opt, k, &p);
							else if (ps.count(opt)) //If last was not a flag
								next = opt;
							else
								pushFlag(opt);
						}
					}
					break;
				case 2: {
					auto start = p;
					bool equal = 0;
					for(;;)
					{
						if (*p == '=')
						{
							equal = 1;
							break;
						}
						else if (*p)
							++p;
						else
							break;
					}

					// This behavior is a little interesting.
					// Basically, it picks an exact match,
					// or the longest real option for which the
					// supplied option is a prefix, *if* there
					// is only one such real option.
					size_t longest = 0;
					const E* corrMatch = 0;
					bool extras = 0;
					for (const auto& [lors, val] : names)
					{
						auto pLongOpt = std::get_if<std::string>(&lors);
						if (pLongOpt &&
								pLongOpt->starts_with(
									std::string_view{start, p}
								))
						{
							if (pLongOpt->size() == p - start)
							{
								longest = pLongOpt->size();
								corrMatch = &val;
								extras = 0;
								break;
							}
							else if (pLongOpt->size() == longest)
								extras = 1;
							else if (pLongOpt->size() >  longest)
							{
								longest = pLongOpt->size();
								corrMatch = &val;
								extras = 0;
							}
						}
					}

					if (corrMatch && !extras)
					{
						if (equal)
							doParse(*corrMatch, k, &++p);
						else if (ps.count(*corrMatch))
							next = *corrMatch;
						else
							pushFlag(*corrMatch);
					}
				} break;
				}
			}
			else
				doParse(std::get<E>(next), k);
		}


		return out;
	}
}


#endif

