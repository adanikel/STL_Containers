#include <iostream>
#include <list>

template <typename T, typename R>
class UnorderedMapIMP
{

	std::list<R>* element_lists; // create SZ lists
	unsigned int arr_sz;

public:
	unsigned int get_hashed_value(T key);
	unsigned int get_hashed_key(unsigned int hashed_value);

	void insert_element(const T key, const R value);
	void delete_element(T key);
	R& at(T key);
	R& operator[](T key);


	UnorderedMapIMP(unsigned int sz); 
	~UnorderedMapIMP();

};

int main()
{
	std::string some_key{ "wassup hombre" };
	UnorderedMapIMP<std::string, int> string_map(5);

	string_map.insert_element(some_key, 10);

	return 0;
}

template <typename T, typename R>
UnorderedMapIMP<T, R>::UnorderedMapIMP<T, R>(unsigned int sz)
	: element_lists{ new std::list<T>[sz] }, arr_sz{ sz }
{}

template <typename T, typename R>
unsigned int UnorderedMapIMP<T, R>::get_hashed_value(T key)
{
	return std::hash<T>{}(key);
}

template <typename T, typename R>
unsigned int UnorderedMapIMP<T, R>::get_hashed_key(unsigned int hashed_value)
{
	return hashed_value % this->arr_sz;
}


template <typename T, typename R>
void UnorderedMapIMP<T, R>::insert_element(const T key, const R value)
{
	unsigned int hashed = this->get_hashed_value(key);
	unsigned int list_idx = this->get_hashed_key(hashed);
	element_lists[list_idx].push_back(value);
}

template <typename T, typename R>
void UnorderedMapIMP<T, R>::delete_element(T key)
{}

template <typename T, typename R>
UnorderedMapIMP<T, R>::~UnorderedMapIMP<T, R>()
{}