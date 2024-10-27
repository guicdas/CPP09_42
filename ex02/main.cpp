#include "PmergeMe.hpp"

static int	isInt( std::string const &s )
{
	int	i;
	int	num;

	i = 0;
	if (s.length() == 0 || s.length() > 12)
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i ]> '9')
			throw (FileException("Error: Argument must be an Integer!"));
		i++;
	}
	num = atoi(s.c_str());
	if (s[i] == '-')
	{
		if (num > 0)
			return (0);
		return (1);
	}
	if (num < 0)
		return (0);
	return (1);
}

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
			if (s.length() < 1 || s.length() > 13 || !isInt(s))
				throw (FileException("Error: Invalid argument!"));

			pmm.push(static_cast<unsigned int> (num));
			i++;
		}
		pmm.showSequence("Before:\t");
		pmm.sort();
		pmm.showSequence("After:\t");
		std::cout << "Time to process a range of\t" << pmm.getVecSize() << " elements with std::vector :\t";
		std::cout << static_cast<double>(pmm.getVecTime() * 1000) / CLOCKS_PER_SEC<< " ms"<< std::endl;
		std::cout << "Time to process a range of\t" << pmm.getLstSize() << " elements with std::list   :\t";
		std::cout << static_cast<double>(pmm.getLstTime() * 1000) / CLOCKS_PER_SEC << " ms"<< std::endl;
		//pmm.printLst();
	}
	catch (std::exception &e){std::cerr << e.what() << std::endl;}
}