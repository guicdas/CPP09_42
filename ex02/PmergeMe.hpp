#pragma once

#include <iostream>
#include <exception>
#include <string>
#include <stdlib.h>
#include <vector>
#include <ctime>

class PMM{
	private:
		std::vector<unsigned int> vec;

	public:
		PMM( void );
		PMM( const PMM &S );
        PMM& operator=( const PMM &S );
		~PMM( void );

	void	push( unsigned int n );
	void	showSequence( char const * s );
	void	sort( void );
};

class FileException : public std::exception{
	private:
		std::string message;

	public:
		FileException( const char* msg );
		~FileException( void ) throw();
		virtual const char* what() const throw();
};