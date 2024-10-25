#include "PmergeMe.hpp"

PMM::PMM( void ) : vec(std::vector<unsigned int>()) {}

PMM::PMM( const PMM &r ){
    std::cout << "PMM Copy called!\n";
    *this = r;
}

PMM& PMM::operator=( const PMM &s ){
    std::cout << "PMM Copy created!\n";
    if (this != &s)
		this->vec = s.vec;
    return (*this);
}

PMM::~PMM( void ) {}

void	mergeInsertSortVector(std::vector<unsigned int> vec){
	(void)vec;
}

void	PMM::sort( void ){
	clock_t startVec = clock();
    mergeInsertSortVector(this->vec);
    clock_t endVec = clock();
	std::cout << static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000 << std::endl;
}

void	PMM::showSequence( char const * s ){
	std::vector<unsigned int>::const_iterator it = this->vec.begin();
	std::cout << s;
	for (;it != this->vec.end() ; it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void	PMM::push( unsigned int n ){
	this->vec.push_back(n);
}

FileException::FileException( const char* msg ) : message(msg) {}
FileException::~FileException( void ) throw() {}
const char * FileException::what( void ) const throw() {
	return (message.c_str());
}
