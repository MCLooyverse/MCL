#ifndef MCL_COMMAND_LINE_ARGUMENT_PARSER_H
#define MCL_COMMAND_LINE_ARGUMENT_PARSER_H

#include <vector>
#include <string>
#include <variant>


namespace mcl
{
	class Args
	{
	public:
		struct ArgSpec;
		struct ArgVal;

		Args(int argc, char** argv, const std::vector<ArgSpec>& as);


		std::vector<ArgVal> operator[](char);
		std::vector<ArgVal> operator[](const std::string&);

	private:
		std::vector<ArgSpec> argspecs;
		std::vector<ArgVal>  sequence;
	};



	struct Args::ArgSpec {
		char s;
		std::string l;
		bool a;

		ArgSpec(char ss, std::string ll, bool aa = 0)
			: s{ss}, l{ll}, a{aa} { }
		ArgSpec(std::string ll, bool aa = 0)
			: s{'\0'}, l{ll}, a{aa} { }
	};
	struct Args::ArgVal {
		size_t id;
		size_t p;
		std::string v;
	};







	Args::Args(int argc, char** argv, const std::vector<ArgSpec>& as)
		: argspecs{as}, sequence{}
	{
		using std::literals::string_literals::operator""s;
		bool literal = 0;
		bool argument = 0;
		for (int i = 0; i < argc; i++)
		{
			if (argument)
			{
				sequence.back().v = argv[i];
				argument = 0;
				continue;
			}
			if (literal)
			{
				sequence.emplace_back(argspecs.size(), i, opt);
				continue;
			}


			int dashes = 0;
			for ( ; dashes < 2 && argv[i][dashes] == '-'; dashes++);

			std::string opt{argv[i] + dashes};

			if (dashes == 0)
				sequence.emplace_back(argspecs.size(), i, opt);
			else if (dashes == 1)
			{
				if (opt.size() == 0)
					sequence.emplace_back(argspecs.size(), i, "-");
				else
				{
					auto j = opt.begin();
					for ( ; j != opt.end() && !argument; j++)
					{
						size_t sp = 0;
						for ( ; sp < argspecs.size(); sp++)
						{
							if (argspecs[sp].s == *j)
							{
								argument = argspecs[sp].a;
								sequence.emplace_back(sp, i, "");

								break;
							}
						}

						if (sp == argspecs.size())
							throw std::domain_error(
									"[mcl::Args] Unrecognized option `-"s +
									*j + "`."
								);
					}

					if (j != opt.end() && argument)
					{
						sequence.back().v.insert(0, j, opt.end());
						argument = 0;
					}
				}
			}
			else if (dashes == 2)
			{
				if (opt.size() == 0)
				{
					sequence.emplace_back(argspecs.size(), i, "--");
					literal = 1;
				}
				else
				{
					auto j = opt.find('=', 1);
					size_t sp = 0;
					if (j == std::string::npos)
					{
						for ( ; sp < argspecs.size(); sp++)
						{
							if (argspecs[sp].l == opt)
								break;
						}
						if (sp == argspecs.size())
							throw std::domain_error(
									"[mcl::Args] Unrecognized option `--"s +
									opt + "`."
								);
						argument = argspecs[sp].a;
						sequence.emplace_back(sp, i, "");
					}
					else
					{
						std::string arg{opt.begin() + j + 1, opt.end()};
						opt.erase(j);
						for ( ; sp < argspecs.size(); sp++)
						{
							if (argspecs[sp].l == opt)
								break;
						}
						if (sp == argspecs.size())
							throw std::domain_error(
									"[mcl::Args] Unrecognized option `--"s +
									opt + "`."
								);
						if (!argspecs[sp].a)
							throw std::domain_error(
									"[mcl::Args] Option `--"s + opt +
									"` does not take an argument."
								);
						sequence.emplace_back(sp, i, arg);
					}
				}
			}
		}
	}


	std::vector<Args::ArgVal> Args::operator[](char c)
	{
		std::vector<ArgVal> out;
		if (c)
		{
			for (const auto& a : sequence)
				if (a.id < argspecs.size() &&
						argspecs[a.id].s == c) out.push_back(a);
		}
		else
		{
			for (const auto& a : sequence)
				if (a.id == argspecs.size()) out.push_back(a);
		}
		return out;
	}

	std::vector<Args::ArgVal> Args::operator[](const std::string& s)
	{
		std::vector<ArgVal> out;
		if (s.size())
		{
			for (const auto& a : sequence)
				if (a.id < argspecs.size() &&
						argspecs[a.id].l == s) out.push_back(a);
		}
		else
		{
			for (const auto& a : sequence)
				if (a.id == argspecs.size()) out.push_back(a);
		}
		return out;
	}
}


#endif

