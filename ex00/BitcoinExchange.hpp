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
		std::map<std::string, float>	db;

	public:
		Exchange( void );
		Exchange( Exchange const & );
		Exchange& operator=( Exchange const & );
		~Exchange( void );
	
	void							parseFile( char const * );
	void							parseLines( std::string const & );
	std::map<std::string, float>&	getMap( void );
};

std::ostream &operator<<( std::ostream & , Exchange & );

class FileException : public std::exception{
	private:
		std::string message;

	public:
		FileException( const char * );
		~FileException( void ) throw();
		virtual const char* what() const throw();
};