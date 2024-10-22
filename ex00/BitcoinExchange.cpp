#include "BitcoinExchange.hpp"

Exchange::Exchange( void ) : database("data.csv"), year(std::list<int>()), month(std::list<int>()), day(std::list<int>()), rate(std::list<int>()){
	std::cout << "Exchange created (No file opened)" << std::endl;
}

Exchange::Exchange( std::string s ) : file(s.c_str()), database("data.csv"), year(std::list<int>()), month(std::list<int>()), day(std::list<int>()), rate(std::list<int>()){
	if (!this->file.is_open())
		throw (FileException("d"));
	if (!this->database.is_open())
		throw (FileException("d"));
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

static int	isFloat(std::string const &s, size_t const &dot){
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
	std::size_t	foundBefore = 0;
	std::size_t	found;
	long long	num;

	found = s.find('-', foundBefore);
	if (found == std::string::npos)
		throw (FileException("Error: database has an empty line!"));
	if (!isInt(s.substr(foundBefore, found)))
		throw (FileException("d"));
	num = std::atoll(s.substr(foundBefore, found).c_str());
	if (num > 2024)
		throw (FileException("d"));
	year.push_back(num);

	foundBefore = found;
	found = s.find('-', foundBefore);
	if (found == std::string::npos)
		throw (FileException("d"));
	if (!isInt(s.substr(foundBefore, found)))
		throw (FileException("d"));
	num = std::atoll(s.substr(foundBefore, found).c_str());
	if (num < 0 || num > 12)
		throw (FileException("d"));
	month.push_back(num);

	foundBefore = found;
	found = s.find('-', foundBefore);
	if (found == std::string::npos)
		throw (FileException("d"));
	if (!isInt(s.substr(foundBefore, found)))
		throw (FileException("d"));
	num = std::atoi(s.substr(foundBefore, found).c_str());
	if (num < 0 || num > 31)
		throw (FileException("d"));
	day.push_back(num);
	
	foundBefore = found;
	found = s.find('-', foundBefore);
	if (found == std::string::npos)
		throw (FileException("d"));
	num = std::atoi(s.substr(0, found).c_str());
	if ((!isInt(s.substr(foundBefore, found))) && (!isFloat(s.substr(foundBefore, found), s.find('.', 0))))
		throw (FileException("d"));
	num = std::atoi(s.substr(foundBefore, found).c_str());
	rate.push_back(num);
}

void Exchange::parseFile( void ){
	std::string	s;

	getline(database, s);
	if (strcmp("date,exchange_rate", s.c_str()) != 0)
		throw (FileException("d"));
	while (getline(database, s))
	{
		if (s.length() < 1)
			throw (FileException("d"));
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


FileException::FileException( const char* msg ) : message(msg) {}
const char * FileException::what( void ) const throw(){
		return (message.c_str());
}
