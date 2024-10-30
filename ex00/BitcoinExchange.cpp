#include "BitcoinExchange.hpp"

Exchange::Exchange( void ) : db(std::map<std::string, float>()){
	std::ifstream	database("data.csv");
	std::string	s;
	int		place;
	float	num;

	if (!database.is_open())
		throw (FileException("Error: Couldn't open database file!"));
	getline(database, s);
	while (getline(database, s))
	{
		place = s.find(',', 0);
		num = std::atof(s.substr(++place, s.size() -1).c_str());
		this->db.insert(std::make_pair(s.substr(0, place - 1), num));
	}
	database.close();
}

Exchange::Exchange( Exchange const &e ){
	*this = e;
}

Exchange& Exchange::operator=( Exchange const &e ){
	if (this == &e)
		return (*this);
	this->db = e.db;
	return (*this);
}

Exchange::~Exchange( void ) {}

static int	isInt( std::string const &s )
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

static int	isFloat( std::string const &s, size_t const &dot ){
	for (int i = dot - 1; i >= 0; i--)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	for (size_t i = dot + 1; i < s.length() ; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}

static long long	findDate( std::string const &s, std::size_t f1, std::size_t f2 ){
	std::string	str;

	if (f1 == std::string::npos || f1 == f2)
		throw (FileException("Error: Bad date formatting (yyyy-mm-dd)!"));
	if (!isInt(s.substr(f2, f1)))
		throw (FileException("Error: date needs to be int!"));
	str = s.substr(f2, f1);
	for (size_t i = 0; i < str.size() && str[i] != '-' ; i++)
	{
		if (str[i] > '9' || str[i] < '0')
			throw (FileException("Error: Invalid character found in Date Value!"));
	}
	return (std::atoll(s.substr(f2, f1).c_str()));
}

static std::string	checkDate( std::string const &s ){
	std::size_t	f1, f2;
	long long	year, month, day;
	std::string	str;
	
	for (size_t u = 3, i = 0; i < s.size() ; i++)
	{
		if (s[i] == '-')
			u--;
		if (!u)
			throw (FileException("Error: Bad date formatting (yyyy-mm-dd)!"));
	}
	f1 = s.find('-', 0);
	year = findDate(s, f1, 0);
	if (year > 2024)
		throw (FileException("Error: Bad year db!"));
	
	f2 = s.find('-', ++f1);
	month = findDate(s, f2, f1);
	if (month > 12 || month < 0)
		throw (FileException("Error: Bad month input!"));
	if (year == 2024 && month > 10)
		throw (FileException("Error: input doesn't exist yet!"));
	if (year < 2009)
		throw (FileException("Error: Only values after 2009!"));

	if (++f2 == s.size() - 1)
		throw (FileException("Error: Bad date formatting (yyyy-mm-dd)!"));
	str = s.substr(f2, s.size());
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] > '9' || str[i] < '0')
			throw (FileException("Error: Invalid character found in Date Value!"));
	}
	day = std::atoll(s.substr(f2, s.size()).c_str());
	if (!isInt(s.substr(f2, s.size())) || (day > 31 || day < 0))
		throw (FileException("Error: Bad day input!"));
	//std::cout << "1: "<< s.substr(0, f1) << " -> " << year << "\n2: "<< s.substr(f1, f2) << " -> " << month << "\n3: "<< s.substr(f2, s.size())  << " -> " << day << std::endl;

	return (s);
}

static void	checkValue( std::string const &s ){
	if (s[0] != ' ')
		throw (FileException("Error: Bad Value formatting (int/float)!"));
	for (std::size_t u = 2, i = 1; i < s.size() ; i++)
	{
		if (s[i] == '-')
			throw (FileException("Error: Not a positive int or float!"));
		if ((s[i] > '9' || s[i] < '0') && s[i] != '.')
			throw (FileException("Error: Invalid character found in Value!"));
		if (s[i] == '.')
			u--;
		if (!u)
			throw (FileException("Error: Invalid character found in Value!"));
	}
}

void	Exchange::parseLines( std::string const &s ){
	std::string	date, substr;
	std::size_t	found;
	float		num;

	found = s.find('|', 0);
	if (found == std::string::npos)
		throw (FileException("Error: Bad file formatting (yyyy-mm-dd | int/float)!"));
	if (s[found - 1] != ' ' || s[found + 1] != ' ')
		throw (FileException("Error: Bad file formatting (yyyy-mm-dd | int/float)!"));
	date = checkDate(s.substr(0, found - 1));
	checkValue(s.substr(++found, s.size()));
	substr = s.substr(++found, s.size());
	num = std::atof(substr.c_str());
	if (!isInt(substr) && isFloat(substr, substr.find('.', 0)) == 0)
		throw (FileException("Error: Value must be an Int or a Float!"));
	if (num < 0 || num > 1000)
		throw (FileException("Error: Value must be between 0 and 1000!"));
	
	std::map<std::string, float>::const_iterator it = this->db.lower_bound(date);
	if (it == this->db.end())
		std::cout << "(" << date << ") "<<  this->db.end()->first << "\t=> " << num << "\t*\t" << this->db.end()->second << "\t= " << it->second * num << std::endl;
	else 
	{
		if (date != it->first && it != this->db.begin())
			--it;
		std::cout << "(" << date << ") "<<  it->first << "\t=> " << num << "\t*\t" << it->second << "\t= " << it->second * num << std::endl;
	}
}

void Exchange::parseFile( char const *inputFile ){
	std::ifstream	file(inputFile);
	std::string	s;

	if (!file.is_open())
		throw (FileException("Error: Couldn't open file!"));
	getline(file, s);
	if (strcmp("date | value", s.c_str()) != 0)
		throw (FileException("Error: Bad file formatting (date | value)!"));
	while (getline(file, s))
	{
		try
		{
			if (s.length() < 1)
				throw (FileException("Error: Empty line!"));
			parseLines(s);
		}
		catch(const std::exception& e){std::cerr << e.what() << std::endl;}
	}
	std::cout << std::endl;
}

std::map<std::string, float>&	Exchange::getMap( void ){
	return (this->db);
}

std::ostream &operator<<( std::ostream &os, Exchange &e ){
	std::map<std::string, float>::const_iterator it = e.getMap().begin();

	for (int i = 0; it != e.getMap().end() ; it++)
		os << i++ << " " << it->first << "| " << it->second << std::endl;
	return (os);
}

FileException::FileException( const char* msg ) : message(msg) {}
FileException::~FileException( void ) throw() {}
const char * FileException::what( void ) const throw() {
	return (message.c_str());
}
