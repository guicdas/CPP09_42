#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include <stdlib.h>

class Exchange{
	private:
		std::ifstream	file;
		std::ifstream	database;
	public:
		std::list<int>	year;
		std::list<int>	month;
		std::list<int>	day;
		std::list<int>	rate;

		Exchange( void );
		Exchange( std::string filename );
		~Exchange( void );
	
	void	parseFile( void );
	void	parseLines( std::string s );

};

std::ostream &operator<<(std::ostream & os, Exchange const &e);


class NotEnoughArgumentsException : public std::exception{
	public:
		virtual const char *what() const throw() {return ("Error: The program must take at least argument!");};
};

class TooManyArgumentsException : public std::exception{
	public:
		virtual const char *what() const throw() {return ("Error: The program must take only one argument!");};
};

class InvalidInputException : public std::exception{
	public:
		virtual const char *what() const throw() {return ("Error: Invalid file!");};
};

class InvalidExtensionException : public std::exception{
	public:
		virtual const char *what() const throw() {return ("Error: File needs to be '.csv'!");};
};

class OpenErrorException : public std::exception{
	public:
		virtual const char *what() const throw() {return ("Error: opening file!");};
};

class BadDatabaseFormattingException : public std::exception{
	public:
		virtual const char *what() const throw() {return ("Error: database isn't formatted as needed!");};
};

class ErrorInDatabaseException : public std::exception{
	public:
		virtual const char *what() const throw() {return ("Error: Be careful an error was found inside the database!");};
};


class InvalidfileFormatException : public std::exception{
	public:
		virtual const char *what() const throw() {return ("Error: bad input (-> yyyy-mm-dd, val)!");};
};

class InvalidYearFormatException : public std::exception{
	public:
		virtual const char *what() const throw() {return ("Error: we're still in 2024!");};
};