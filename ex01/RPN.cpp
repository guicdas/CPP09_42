#include "RPN.hpp"

RPN::RPN( void ) : stack(std::stack<int>()) {}

RPN::RPN( const RPN &r ){
    std::cout << "RPN Copy called!\n";
    *this = r;
}

RPN& RPN::operator=( const RPN &r ){
	std::cout << "RPN Copy created!\n";
	if (this != &r)
		this->stack = r.stack;
	return (*this);
}

RPN::~RPN( void ) {}

void	RPN::push( char c ) {
	this->stack.push(c);
}

void	RPN::pop( void ) {
	this->stack.pop();
}

void	RPN::compute( char c ) {
	int	right, left;

	if (c < '9' && c > '0')
		this->stack.push(c - 48);
	else
	{
		if (this->stack.size() < 2)
			throw (FileException("Error: Operator has no argument!"));
		right = this->stack.top();
		this->stack.pop();
		left = this->stack.top();
		this->stack.pop();

		switch(c){
			case '+': this->stack.push(left + right); break;
			case '-': this->stack.push(left - right); break;
			case 'x': this->stack.push(left * right); break;
			case '/': this->stack.push(left / right); break;
			default: std::cout << "Something went horribly wrong!\n"; break;
		}
	}
}

int	RPN::top( void ) {
	return (this->stack.top());
}

int	RPN::result( void ) {
	if (this->stack.size() > 1)
		throw (FileException("Error: Too much numbers!"));
	return (this->stack.top());
}

FileException::FileException( const char* msg ) : message(msg) {}
FileException::~FileException( void ) throw() {}
const char * FileException::what( void ) const throw() {
	return (message.c_str());
}
