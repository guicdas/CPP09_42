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
		RPN( const RPN & );
        RPN& operator=( const RPN & );
		~RPN( void );

	void	push( char c );
	void	pop( void );
	int		top( void );
	void	compute( char c );
	int		result( void );
};

class FileException : public std::exception{
	private:
		std::string	message;

	public:
		FileException( const char* msg );
		~FileException( void ) throw();
		virtual const char* what() const throw();
};