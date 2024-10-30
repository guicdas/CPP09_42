#include "PmergeMe.hpp"

PMM::PMM( void ) : vec(std::vector<unsigned int>()) , lst(std::list<unsigned int>()) {}

PMM::PMM( PMM const &p ){
	std::cout << "PMM Copy called!\n";
	*this = p;
}

PMM& PMM::operator=( PMM const &p ){
	std::cout << "PMM Copy created!\n";
	if (this == &p)
		return (*this);
	this->vec = p.vec;
	this->lst = p.lst;
	return (*this);
}

PMM::~PMM( void ) {}

static void mergeVectors(std::vector<unsigned int> &vec, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	int i = 0, j = 0, k = left;

	std::vector<unsigned int> L(n1);
	std::vector<unsigned int> R(n2);

	for (int j = 0; j < n1; j++)
		L[j] = vec[left + j];
	for (int j = 0; j < n2; j++)
		R[j] = vec[mid + 1 + j];

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
			vec[k] = L[i++];
		else
			vec[k] = R[j++];
		k++;
	}

	while (i < n1)
		vec[k++] = L[i++];
	while (j < n2)
		vec[k++] = R[j++];
}

static void	mergeInsertSortVector(std::vector<unsigned int> &vec, int left, int right){	
	int	temp;
	
	if (right - left < 2)
	{
		if (vec[left] > vec[right])
		{
			temp = vec[right];
			vec[right] = vec[left];
			vec[left] = temp;
		}
	}
	else
	{
		mergeInsertSortVector(vec, left, left + (right - left) / 2);
		mergeInsertSortVector(vec, (left + (right - left) / 2) + 1, right);
		mergeVectors(vec, left, left + (right - left) / 2, right);
	}
}

static std::list<unsigned int>	mergeLists( std::list<unsigned int> &l, std::list<unsigned int> &r ){
	std::list<unsigned int>::iterator	it1 = l.begin();
	std::list<unsigned int>::iterator	it2 = r.begin();
	std::list<unsigned int>				result;

	while (it1 != l.end() && it2 != r.end())
	{
		if (*it1 < *it2)
			result.push_back(*it1++);
		else
		{
			result.push_back(*it2);
			++it2;
		}
	}
	result.insert(result.end(), it1, l.end());
	result.insert(result.end(), it2, r.end());

	//std::cout << result << std::endl;
	return result;
}

static std::list<unsigned int>	mergeInsertSortList( std::list<unsigned int> &lst ){	
	std::list<unsigned int>::iterator	it, itemp;
	std::list<unsigned int>				left, right;

	if (lst.size() < 3)
	{
		it = lst.begin();
		itemp = it++;
		if (*it < *itemp)
			lst.reverse();
		return (lst);
	}
	it = lst.begin();
	std::advance(it, lst.size() / 2);

	left.splice(left.end(), lst, lst.begin(), it);
	//std::cout << "left: " << left << std::endl;
	right.splice(right.end(), lst, it, lst.end());
	//std::cout << "right: " << right << std::endl;

	left = mergeInsertSortList(left);
	right = mergeInsertSortList(right);

	return (mergeLists(left, right));
}

void	PMM::sort( void ){
	this->vecTime = std::clock();
	mergeInsertSortVector(this->vec, 0, this->vec.size() - 1);
	this->vecTime =  std::clock() - this->vecTime;
	if (!isSorted(this->vec.begin(), this->vec.end()) || this->vec.size() < 1)
		throw (FileException("Vector wasn't sorted!"));
	
	this->lstTime = std::clock();
	this->lst = mergeInsertSortList(this->lst);
	this->lstTime = std::clock() - this->lstTime;
	if (!isSorted(this->lst.begin(), this->lst.end()) || this->lst.size() < 1)
		throw (FileException("List wasn't sorted!"));
}

clock_t	PMM::getVecTime( void ){
	return (this->vecTime);
}

int	PMM::getVecSize( void ){
	return (this->vec.size());
}

void	PMM::printLst( void ){
	std::cout << this->lst << std::endl;
}

clock_t	PMM::getLstTime( void ){
	return (this->lstTime);
}

int	PMM::getLstSize( void ){
	return (this->lst.size());
}

void	PMM::showSequence( char const * s ){
	std::vector<unsigned int>::const_iterator it = this->vec.begin();
	int	i = 0;

	std::cout << s;
	for (;it != this->vec.end() && i < 5 ; it++, i++)
		std::cout << *it << " ";
	if (i == 5 && it != this->vec.end())
		std::cout << "[...]";
	std::cout << "\t(" << this->vec.size() << ")" << std::endl;
}

void	PMM::push( unsigned int n ){
	this->vec.push_back(n);
	this->lst.push_back(n);
}

std::ostream &operator<<( std::ostream &os, std::list<unsigned int> const &l ) {
	std::list<unsigned int>::const_iterator it = l.begin();

	os << "Printing list with " << l.size() << " elements:\n";
	for (int i = 0; it != l.end(); ++it)
		os << "i: " << i++ << "\t" << *it << "\n";

	return (os);
}

FileException::FileException( const char* msg ) : message(msg) {}
FileException::~FileException( void ) throw() {}
const char * FileException::what( void ) const throw() {
	return (message.c_str());
}
