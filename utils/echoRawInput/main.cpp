#include <iostream>
#include "../../ttymanip.h"
#include "../../strmanip.h"


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << *argv << " <quit character>\n";
		return 1;
	}

	std::string ql = argv[1];
	char quit = '\0';
	if (ql[0] == '^')
		quit = (ql.size() == 1 ? '^' : ql[1] ^ 0x40);
	else if (ql[0] == '\\')
		quit = (ql.size() == 1 ? '\\' :
				ql[1] == 'a' ? '\a' :
				ql[1] == 'b' ? '\b' :
				ql[1] == 'e' ? '\x1B' :
				ql[1] == 'f' ? '\f' :
				ql[1] == 'n' ? '\n' :
				ql[1] == 'r' ? '\r' :
				ql[1] == 't' ? '\t' :
				ql[1] == 'v' ? '\v' :
				ql[1]);
	else
		quit = ql[0];

	mcl::tty::init();


	for (char c; c = mcl::tty::get(), c != quit; )
		std::cout << makePrintable(c, 3) << "\n";
	return 0;
}
