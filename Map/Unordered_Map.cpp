#include <iostream>
#include <list>

// unordered_map implementation, which an array of buckets where each bucket is a std::list containing std::pairs

template <typename T, typename R>
class UnorderedMap
{

	const unsigned int _DEF_BUCKETS_SZ{ 100 };
	unsigned int buckets_sz;
	unsigned int get_hashed_value(const T key) const;
	unsigned int get_hashed_key(unsigned int hashed_value) const;

	R* search_within_specific_list(unsigned int list_idx, const T key);

public:
	std::list<std::pair<T, R>>* element_lists; // create SZ lists

	UnorderedMap(); // default bucket num
	UnorderedMap(unsigned int sz); // todo: make const
	UnorderedMap(const UnorderedMap<T, R>& map_obj); // copy constructor
	UnorderedMap(UnorderedMap<T, R>&& map_obj); // move constructor

	UnorderedMap<T, R>& operator=(const UnorderedMap<T, R>& map_obj); // copy assignment
	UnorderedMap<T, R>& operator=(UnorderedMap<T, R>&& map_obj); // move assignment

	void insert_element(const T key, const R value);
	void delete_element(const T key);

	bool empty() const;
	bool contains(const T key);
	unsigned int size() const;
	unsigned int max_size() const;

	void clear();
	void swap(UnorderedMap<T, R>& map_obj);
	unsigned int bucket_size(unsigned int bucket_idx) const; // size of bucket

	R& at(T key);
	R& operator[](T key);

	~UnorderedMap();

};

int main()
{
	std::string some_key{ "some_key_1" };
	std::string non_existing_key{ "some_key_2" };
	UnorderedMap<std::string, int> string_map(5);

	string_map.insert_element(some_key, 10);

	std::cout << string_map.at(some_key);
	std::cout << string_map.at(non_existing_key);
	std::cout << "\n\n";
	std::cout << string_map[some_key];
	string_map.insert_element(some_key, 11);
	std::cout << string_map[some_key];
	string_map.delete_element(some_key);
	std::cout << "\n" << string_map[some_key];
	string_map[some_key] = 999;
	UnorderedMap<std::string, int> string_map2(string_map);
	std::cout << "\ncopied const" << string_map2[some_key];
	string_map[some_key] = 888;
	string_map2 = string_map;
	std::cout << "\ncopied assign" << string_map2[some_key];
	std::cout << "\ncontains some_key" << string_map2.contains(some_key);

	string_map2[some_key] = 7777;
	std::cout << "\nbefore swapping" << string_map2[some_key];

	string_map.swap(string_map2);
	std::cout << "\nafter swapping" << string_map2[some_key];
	std::cout << "\nsize of bucket 0 is " << string_map.bucket_size(0);


	return 0;
}

template <typename T, typename R>
UnorderedMap<T, R>::UnorderedMap()
	: buckets_sz{ _DEF_BUCKETS_SZ }, element_lists{ new std::list<std::pair<T, R>>[buckets_sz] }
{}

template <typename T, typename R>
UnorderedMap<T, R>::UnorderedMap(unsigned int sz)
	: buckets_sz{ sz }, element_lists{ new std::list<std::pair<T, R>>[buckets_sz] }
{}

template <typename T, typename R>
UnorderedMap<T, R>::UnorderedMap(const UnorderedMap<T, R>& map_obj)
	: buckets_sz{ map_obj.buckets_sz }, element_lists{ new std::list<std::pair<T, R>>[buckets_sz] }  // copy buckets_sz
{
	unsigned int bucket_idx{ 0 };
	while (bucket_idx < buckets_sz) // copy all buckets
	{
		this->element_lists[bucket_idx] = map_obj.element_lists[bucket_idx];
		bucket_idx++;
	}

}

template <typename T, typename R>
UnorderedMap<T, R>::UnorderedMap(UnorderedMap<T, R>&& map_obj)
	: buckets_sz{ std::move(map_obj.buckets_sz) }, element_lists{ new std::list<std::pair<T, R>>[buckets_sz] }
{
	unsigned int bucket_idx{ 0 };
	while (bucket_idx < buckets_sz) // copy all buckets
	{
		this->element_lists[bucket_idx] = std::move(map_obj.element_lists[bucket_idx]);
		bucket_idx++;
	}

}

template <typename T, typename R>
UnorderedMap<T, R>& UnorderedMap<T, R>::operator=(const UnorderedMap<T, R>& map_obj)
{
	this->buckets_sz = map_obj.buckets_sz;
	this->clear();

	unsigned int bucket_idx{ 0 };
	while (bucket_idx < buckets_sz)
	{
		this->element_lists[bucket_idx] = map_obj.element_lists[bucket_idx];
		bucket_idx++;
	}

	return *this;
}

template <typename T, typename R>
UnorderedMap<T, R>& UnorderedMap<T, R>::operator=(UnorderedMap<T, R>&& map_obj)
{
	this->buckets_sz = std::move(map_obj.buckets_sz);
	this->clear();

	unsigned int bucket_idx{ 0 };
	while (bucket_idx < buckets_sz)
	{
		this->element_lists[bucket_idx] = std::move(map_obj.element_lists[bucket_idx]);
		bucket_idx++;
	}

	return *this;
}

template <typename T, typename R>
unsigned int UnorderedMap<T, R>::get_hashed_value(const T key) const // hashes key into unsigned int
{
	return std::hash<T>{}(key);
}

template <typename T, typename R>
unsigned int UnorderedMap<T, R>::get_hashed_key(unsigned int hashed_value) const // converts hashed unsigned int into index
{
	return hashed_value % this->buckets_sz;
}

template <typename T, typename R>
R* UnorderedMap<T, R>::search_within_specific_list(unsigned int list_idx, const T key)
{
	R* value = nullptr;
	typename std::list<std::pair<T, R>>::iterator itr = this->element_lists[list_idx].begin();

	while (itr != this->element_lists[list_idx].end())
	{
		if (itr->first == key)
		{
			value = &(itr->second);
			break;
		}
		itr++;
	}

	return value;
}

template <typename T, typename R>
R& UnorderedMap<T, R>::at(const T key)
{
	unsigned int hashed = this->get_hashed_value(key);
	unsigned int list_idx = this->get_hashed_key(hashed);

	R* value_addr = this->search_within_specific_list(list_idx, key);
	if (!value_addr)
	{
		R default_value{};
		this->insert_element(key, default_value);
	}
	value_addr = this->search_within_specific_list(list_idx, key);

	return *value_addr;
}

template <typename T, typename R>
R& UnorderedMap<T, R>::operator[](const T key)
{
	unsigned int hashed = this->get_hashed_value(key);
	unsigned int list_idx = this->get_hashed_key(hashed);

	R* value_addr = this->search_within_specific_list(list_idx, key);
	if (!value_addr)
	{
		R default_value{};
		this->insert_element(key, default_value);
	}
	value_addr = this->search_within_specific_list(list_idx, key);

	return *value_addr;
}


template <typename T, typename R>
void UnorderedMap<T, R>::insert_element(const T key, const R value)
{
	unsigned int hashed = this->get_hashed_value(key);
	unsigned int list_idx = this->get_hashed_key(hashed);

	R* existing_value = this->search_within_specific_list(list_idx, key);

	if (existing_value) *existing_value = value; // overwrite if exists
	else element_lists[list_idx].push_back(std::make_pair(key, value));
}

template <typename T, typename R>
void UnorderedMap<T, R>::delete_element(const T key)
{
	unsigned int hashed = this->get_hashed_value(key);
	unsigned int list_idx = this->get_hashed_key(hashed);

	typename std::list<std::pair<T, R>>::iterator itr = this->element_lists[list_idx].begin();

	while (itr != this->element_lists[list_idx].end())
	{
		if (itr->first == key)
		{
			this->element_lists[list_idx].erase(itr);
			break;
		}
		itr++;
	}
}

template <typename T, typename R>
bool UnorderedMap<T, R>::contains(const T key)
{
	unsigned int hashed = this->get_hashed_value(key);
	unsigned int list_idx = this->get_hashed_key(hashed);

	R* existing_value = this->search_within_specific_list(list_idx, key);

	return bool(existing_value);
}

template <typename T, typename R>
unsigned int UnorderedMap<T, R>::size() const
{

	unsigned int size{ 0 };
	unsigned int bucket_idx{ 0 };
	while (bucket_idx < buckets_sz)
	{
		size += this->element_lists[bucket_idx].size();
		bucket_idx++;
	}

	return size;
}

template <typename T, typename R>
unsigned int  UnorderedMap<T, R>::max_size() const
{
	unsigned int max_size{ 0 };
	unsigned int bucket_idx{ 0 };
	while (bucket_idx < buckets_sz)
	{
		max_size += this->element_lists[bucket_idx].max_size();
		bucket_idx++;
	}

	return max_size;
}


template <typename T, typename R>
bool UnorderedMap<T, R>::empty() const
{
	unsigned int bucket_idx{ 0 };
	while (bucket_idx < buckets_sz)
	{
		if (!this->element_lists[bucket_idx].empty())
		{
			return 0;
		};
		bucket_idx++;
	}
	return 1;
}

template <typename T, typename R>
void UnorderedMap<T, R>::clear()
{
	delete[] this->element_lists;
	this->element_lists = new std::list<std::pair<T, R>>[buckets_sz];
}

template <typename T, typename R>
void UnorderedMap<T, R>::swap(UnorderedMap<T, R>& map_obj)
{
	std::swap(this->element_lists, map_obj.element_lists);
	std::swap(this->buckets_sz, map_obj.buckets_sz);
}

template <typename T, typename R>
unsigned int UnorderedMap<T, R>::bucket_size(unsigned int bucket_idx) const
{
	return this->element_lists[bucket_idx].size();
}


template <typename T, typename R>
UnorderedMap<T, R>::~UnorderedMap<T, R>()
{
	delete[] this->element_lists;
}
