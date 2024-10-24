#include "RPN.hpp"

int main(int ac, char ** av){
	std::string s;
	int	i = 1;

	try
	{
		RPN rpn;

		if (ac < 2)
			throw (FileException("Error: No arguments found!"));
		while (av[i])
		{
			s = av[i];
			if (s.length() != 1)
				throw (FileException("Error: Invalid argument!"));
			if (s[0] != '+' && s[0] != '-' && s[0] != 'x' && s[0] != '/' && (s[0] > '9' || s[0] < '0'))
				throw (FileException("Error: Syntax error!"));
			rpn.compute(s[0]);
			i++;
		}
		std::cout << rpn.result() << std::endl;
	}
	catch (std::exception &e){std::cerr << e.what() << std::endl;}
}