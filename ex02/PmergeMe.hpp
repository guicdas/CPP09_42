#pragma once

#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <list>
#include <ctime>		//clock
#include <algorithm>
#include <iomanip>		//fixed, precision
#include <iterator>

template <typename T>
static int	isSorted( T begin, T const &end){
	for(long temp = -1; begin != end ;begin++)
	{
		if (static_cast<long>(*begin) < temp)
			return (0);
		temp = *begin;
	}
	return (1);
}

class PMM{
	private:
		std::vector<unsigned int>	vec;
		clock_t						vecTime;
		std::list<unsigned int>		lst;
		clock_t						lstTime;

	public:
		PMM( void );
		PMM( const PMM & );
        PMM& operator=( const PMM & );
		~PMM( void );

	void	push( unsigned int );
	void	showSequence( char const * );
	void	sort( void );
	clock_t	getVecTime( void );
	int		getVecSize( void );
	void	printLst( void );
	clock_t	getLstTime( void );
	int		getLstSize( void );
};

std::ostream &operator<<(std::ostream &os, std::list<unsigned int> const &l);

class FileException : public std::exception{
	private:
		std::string message;

	public:
		FileException( const char* );
		~FileException( void ) throw();
		virtual const char* what() const throw();
};