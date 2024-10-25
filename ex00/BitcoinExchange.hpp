#pragma once

#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <utility>
#include <stdlib.h>
#include <iterator>
#include <iomanip>

class Exchange{
	private:
		std::ifstream	file;
		std::ifstream	database;

	public:
		std::map<std::string, float>	db;
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
		FileException( const char* msg );
		~FileException( void ) throw();
		virtual const char* what() const throw();
};