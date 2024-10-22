#include "BitcoinExchange.hpp"

Exchange::Exchange( void ) : database("data.csv"), year(std::list<int>()), month(std::list<int>()), day(std::list<int>()), rate(std::list<int>()){
	std::cout << "Exchange created (No file opened)" << std::endl;
}

Exchange::Exchange( std::string s ) : file(s.c_str()), database("data.csv"), year(std::list<int>()), month(std::list<int>()), day(std::list<int>()), rate(std::list<int>()){
	if (!this->file.is_open())
		throw (OpenErrorException());
	if (!this->database.is_open())
		throw (OpenErrorException());
}

Exchange::~Exchange( void ){
	std::cout << "File and database closed" << std::endl;
	this->file.close();
	this->database.close();
}

static int	isInt(const std::string& s)
{
	int	i;
	int	num;

	i = 0;
	if (s.length() == 0 || s.length() > 12)
		return (0);
	num = atoi(s.c_str());
	if (s[i] == '-')
	{
		if (num > 0)
			return (0);
		return (1);
	}
	if (num < 0)
		return (0);
	return (1);
}

static int	isFloat(const std::string& s, size_t& dot)
{
	for (int i = dot - 1; i >= 0; i--)
	{
		if ((s[i] < '0' || s[i] > '9') && i != 0)
			return (0);
		if ((s[i] < '0' || s[i] > '9') && i == 0 && s[i] != '+' && s[i] != '-')
			return (0);
	}
	for (size_t i = dot + 1; i < s.length() ; i++)
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != 'f')
			return (0);
		if (s[i] == 'f' && i != s.length() - 1)
			return (0);
	}
	return (1);
}

void	Exchange::parseLines( std::string s ){
	std::size_t	num;
	std::size_t	found;
	std::size_t	foundBefore;

	found = s.find('-', 0);
	if (found == std::string::npos)
		throw (InvalidfileFormatException());
	num = std::atoi(s.substr(0, found).c_str());
	if (num > 2024)
		throw (ErrorInDatabaseException());
	year.push_back(num);

	foundBefore = found;
	found = s.find('-', foundBefore);
	if (found == std::string::npos)
		throw (InvalidfileFormatException());
	num = std::atoi(s.substr(foundBefore, found).c_str());
	if (num < 0 || num > 12)
		throw (ErrorInDatabaseException());
	month.push_back(num);

	foundBefore = found;
	found = s.find('-', foundBefore);
	if (found == std::string::npos)
		throw (InvalidfileFormatException());
	num = std::atoi(s.substr(foundBefore, found).c_str());
	if (!isInt(num, s.find('.')<-) && !isFloat(num, s.find('.')))
		throw (ErrorInDatabaseException());
	day.push_back(num);
	
	foundBefore = found;
	found = s.find('-', foundBefore);
	found = s.find('-', found);
	if (found == std::string::npos)
		throw (InvalidfileFormatException());
	num = std::atoi(s.substr(0, found).c_str());
	if (num < 0 || num > 31)
		throw (ErrorInDatabaseException());
	rate.push_back(num);
}

void Exchange::parseFile( void ){
	std::string	s;

	getline(database, s);
	if (strcmp("date,exchange_rate", s.c_str()) != 0)
		throw (BadDatabaseFormattingException());
	while (getline(database, s))
	{
		if (s.length() < 1)
			throw (ErrorInDatabaseException());
		parseLines(s);
	}
}

std::ostream &operator<<(std::ostream & os, Exchange const &e){
	std::list<int>::const_iterator itYear = e.year.begin();
	std::list<int>::const_iterator itMonth = e.month.begin();
	std::list<int>::const_iterator itDay = e.day.begin();
	std::list<int>::const_iterator itRate = e.rate.begin();

	for (; itYear != e.year.end() ; itYear++, itMonth++, itDay++, itRate++)
		os << *itYear << "-" << *itMonth << "-" << *itDay << ", "<< *itRate << std::endl;
	return (os);
}