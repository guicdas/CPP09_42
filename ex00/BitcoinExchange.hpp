#pragma once

#include <iostream>
#include <exception>
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

class FileException : public std::exception{
	private:
		std::string message;

	public:
		explicit	FileException( const char* msg );
		virtual const char* what() const throw();
};