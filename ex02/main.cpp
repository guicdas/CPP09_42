#include "PmergeMe.hpp"

int main(int ac, char ** av){
	std::string s;
	long		num;
	int			i = 1;

	try
	{
		PMM pmm;

		if (ac < 2)
			throw (FileException("Error: No arguments found!"));
		while (av[i])
		{
			s = av[i];
			num = std::atol(s.c_str());
			if (s.length() > 13 || num < 0 || num > 2147483647)
				throw (FileException("Error: Invalid argument!"));

			pmm.push(static_cast<unsigned int> (num));
			i++;
		}
		pmm.showSequence("Before:\t");
		pmm.sort();
		pmm.showSequence("After:\t");
	}
	catch (std::exception &e){std::cerr << e.what() << std::endl;}
}