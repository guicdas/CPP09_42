#include "RPN.hpp"

int main(int ac, char ** av){
	std::string	s;
	size_t		i = 0;

	try
	{
		RPN	rpn;

		if (ac != 2)
			throw (FileException("Error: Need one and only argument!"));
		s = av[1];
		if (s.length() < 1)
			throw (FileException("Error: Empty argument!"));
		while (s[i])
		{
			if (s[i] == ' ')
			{
				i++;
				continue ;
			}
			else if (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && (s[i] > '9' || s[i] < '0'))
				throw (FileException("Error: Syntax error!"));
			else
				rpn.compute(s[i]);
			i++;
		}
		std::cout << rpn.result() << std::endl;
	}
	catch (std::exception &e){std::cerr << e.what() << std::endl;}
}
