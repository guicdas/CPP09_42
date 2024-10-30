#pragma once

#include <iostream>
#include <exception>
#include <fstream>
#include <stack>
#include <string>

class RPN{
	private:
		std::stack<int>	stack;

	public:
		RPN( void );
		RPN( RPN const & );
        RPN& operator=( RPN const & );
		~RPN( void );

	void	push( long long );
	void	pop( void );
	int		top( void );
	void	compute( char );
	int		result( void );
};

class FileException : public std::exception{
	private:
		std::string	message;

	public:
		FileException( const char * );
		~FileException( void ) throw();
		virtual const char* what() const throw();
};