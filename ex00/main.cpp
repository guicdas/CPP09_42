#include "BitcoinExchange.hpp"

int main(int ac, char ** av){
	try
	{
		if (ac < 2)
			throw (NotEnoughArgumentsException());
		if (ac > 2)
			throw (TooManyArgumentsException());
		if (strlen(av[1]) < 1)
			throw (InvalidInputException());
		std::string filename(av[1]);
		Exchange	btc(filename);
		btc.parseFile();
		std::cout << btc <<std::endl;
	}
	catch (std::exception &e){std::cout << e.what() << std::endl;}
}



		/*
		if (strncmp(".txt", filename.substr(filename.length() - 4,4).c_str(), 4) != 0)
			throw (InvalidExtensionException());*/