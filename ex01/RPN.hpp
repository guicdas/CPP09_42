#pragma once

#include <iostream>
#include <exception>
#include <fstream>
#include <stack>
#include <string>
#include <sstream>

class RPN{
	private:
		std::stack<int>	stack;
		int			nOps;

	public:
		RPN( void );
		RPN( const RPN &S );
        RPN& operator=( const RPN &S );
		~RPN( void );

	void	push( char c );
	void	pop( void );
	int		top( void );
	void	compute( char c );
	int		result( void );
};

class FileException : public std::exception{
	private:
		std::string message;

	public:
		FileException( const char* msg );
		~FileException( void ) throw();
		virtual const char* what() const throw();
};