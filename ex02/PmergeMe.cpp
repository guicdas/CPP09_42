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

static int	isVecSorted(std::vector<unsigned int> &vec){
	std::vector<unsigned int>::const_iterator it = vec.begin();

	for(long temp = -1; it != vec.end() ;it++)
	{
		if (static_cast<long>(*it) < temp)
			return (0);
		temp = *it;
	}
	return (1);
}

void mergeVectors(std::vector<unsigned int> &vec, int left, int mid, int right) {
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

void	mergeInsertSortVector(std::vector<unsigned int> &vec, int left, int right){	
	if (right - left < 2)
	{
		// std::cout << vec[left] << " > "<< vec[right] <<"\n";
		if (vec[left] > vec[right])
		{
			int	temp = vec[right];
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

void	PMM::sort( void ){
	clock_t start;
	start = clock();
	mergeInsertSortVector(this->vec, 0, this->vec.size() - 1);
	start = clock() - start;
	std::cout << "Time to process a range of " << this->vec.size() << " elements with std::vector :\t" << static_cast<float>(start) *1000 / CLOCKS_PER_SEC << std::endl;
	if (!isVecSorted(this->vec))
		throw (FileException("Vector wasn't sorted!"));
	
}

void	PMM::showSequence( char const * s ){
	std::vector<unsigned int>::const_iterator it = this->vec.begin();
	std::cout << s;
	for (;it != this->vec.end() ; it++)
		std::cout << *it << " ";
	std::cout << "\t(" << this->vec.size() << ")" << std::endl;
}

void	PMM::push( unsigned int n ){
	this->vec.push_back(n);
}

FileException::FileException( const char* msg ) : message(msg) {}
FileException::~FileException( void ) throw() {}
const char * FileException::what( void ) const throw() {
	return (message.c_str());
}
