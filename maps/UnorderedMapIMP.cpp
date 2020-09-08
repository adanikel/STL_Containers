#include <iostream>
#include <list>

template <typename T, typename R>
class UnorderedMapIMP
{

	std::list<std::pair<T, R>>* element_lists; // create SZ lists
	unsigned int arr_sz;
	unsigned int get_hashed_value(T key);
	unsigned int get_hashed_key(unsigned int hashed_value);

	R* search_within_specific_list(unsigned int list_idx, T key);


public:
	void insert_element(const T key, const R value);
	void delete_element(T key);

	void at(T key);  // todo: return ref R
	//R& operator[](T key);


	UnorderedMapIMP(unsigned int sz);
	~UnorderedMapIMP();

};

int main()
{
	std::string some_key{ "wassup hombre" };
	UnorderedMapIMP<std::string, int> string_map(5);

	string_map.insert_element(some_key, 10);

	string_map.at(some_key);

	return 0;
}

template <typename T, typename R>
UnorderedMapIMP<T, R>::UnorderedMapIMP(unsigned int sz)
	: element_lists{ new std::list<std::pair<T, R>>[sz] }, arr_sz{ sz }
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
R* UnorderedMapIMP<T, R>::search_within_specific_list(unsigned int list_idx, T key)
{
	R* value = nullptr;
	typename std::list<std::pair<T, R>>::iterator itr = this->element_lists[list_idx].begin();


	while (itr != this->element_lists[list_idx].end())
	{
		if (itr->first == key) value = &(itr->second);
		itr++;
	}

	return value;
}

template <typename T, typename R>
void UnorderedMapIMP<T, R>::at(T key)
{
	unsigned int hashed = this->get_hashed_value(key);
	unsigned int list_idx = this->get_hashed_key(hashed);

	R* value_addr = this->search_within_specific_list(list_idx, key);
	if (value_addr) std::cout << *value_addr;
	else std::cout << "non existing";

}

template <typename T, typename R>
void UnorderedMapIMP<T, R>::insert_element(const T key, const R value)
{
	unsigned int hashed = this->get_hashed_value(key);
	unsigned int list_idx = this->get_hashed_key(hashed);
	element_lists[list_idx].push_back(std::make_pair(key, value));
}

template <typename T, typename R>
void UnorderedMapIMP<T, R>::delete_element(T key)
{}

template <typename T, typename R>
UnorderedMapIMP<T, R>::~UnorderedMapIMP<T, R>()
{}