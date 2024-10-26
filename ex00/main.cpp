#include "BitcoinExchange.hpp"

int main(int ac, char ** av){
	try
	{
		if (ac < 2)
			throw (FileException("Error: The program must take at least one argument!"));
		if (ac > 2)
			throw (FileException("Error: The program must take only one argument!"));
		if (strlen(av[1]) < 1)
			throw (FileException("Error: Invalid file!"));
		Exchange	btc;
		btc.parseFile(av[1]);
		//std::cout << "\n" << btc <<std::endl;
	}
	catch (std::exception &e){std::cout << e.what() << std::endl;}
}