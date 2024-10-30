#include "RPN.hpp"

RPN::RPN( void ) : stack(std::stack<int>()) {}

RPN::RPN( RPN const &r ){
    std::cout << "RPN Copy called!\n";
    *this = r;
}

RPN& RPN::operator=( RPN const &r ){
	std::cout << "RPN Copy created!\n";
	if (this != &r)
		this->stack = r.stack;
	return (*this);
}

RPN::~RPN( void ) {}

void	RPN::push( long long c ) {
	this->stack.push(c);
}

void	RPN::pop( void ) {
	this->stack.pop();
}

void	RPN::compute( char c ) {
	long long	right, left;

	if (c <= '9' && c >= '0')
		push(c - 48);
	else if (c == '+' || c == '-' || c == '*' || c == '/')
	{
		if (this->stack.size() < 2)
			throw (FileException("Error: Wrong operator syntax!"));
		right = this->stack.top();
		this->stack.pop();
		left = this->stack.top();
		this->stack.pop();
		//std::cout << right << " " << c << " " << left << std::endl;;
		if (left > 2147483647 || right > 2147483647 || left < -2147483648 || right < -2147483648)
			throw (FileException("Error: Operation will result in overflow!"));
		switch(c){
			case '+':	push(left + right); break;
			case '-':	push(left - right); break;
			case '*':	if (left * right > 2147483647)
							throw (FileException("Error: Operation will result in overflow!"));
						push(left * right); break;
			case '/':	if (right == 0)
							throw (FileException("Error: Division by 0 prohibited!"));
						push(left / right); break;
			default: std::cout << "Something went horribly wrong!\n"; break;
		}
	}
	else
		throw (FileException("Error: Wrong argument!"));
}

int	RPN::top( void ) {
	return (this->stack.top());
}

int	RPN::result( void ) {
	if (this->stack.size() > 1)
		throw (FileException("Error: Too much numbers!"));
	if (this->stack.size() < 1)
		throw (FileException("Error: No arguments!"));
	return (this->stack.top());
}

FileException::FileException( const char* msg ) : message(msg) {}
FileException::~FileException( void ) throw() {}
const char * FileException::what( void ) const throw() {
	return (message.c_str());
}
