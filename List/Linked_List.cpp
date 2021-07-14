#include <iostream>

// Linked list


// todo pop if one element just clear
// todo incr and decr size in pops
// todo make sure current link is correct

template <typename T>
struct Link
{
	Link<T>* next;
	Link<T>* prev;
	T value;

	explicit Link(const T obj); // no default constructor

	Link<T>* operator->();

	~Link();

};

template <typename T>
class List
{
private:
	Link<T>* current_link; // pointer to link. Value inside will not be through a pointer
	unsigned int size; // modify every addition / deletion

public:
	Link<T>* first; // begin() returns this
	Link<T>* last;

	List(); // initialize all links as nullptr
	List(T obj);
	explicit List(std::initializer_list<T> list_objs); // to user 'Vec{a, b, c}'

	List(const List<T>& link_obj); // copy constructor
	List(List<T>&& link_obj); // move constructor

	List<T>& operator=(const List<T>& link_obj); // copy assignment. note that there's operator= definition for T values
	List<T>& operator=(List<T>&& link_obj); // move assignment

	void push_back(T obj);
	void push_front(T obj);
	void pop_back();
	void pop_front();

	inline bool empty() const;

	void clear();

	T& operator=(T obj); // return current value, unlike copy assignment

	struct iterator
	{
		Link<T>* current;

		iterator(Link<T>* init);

		T& operator*();

		iterator& operator++();
		iterator& operator--();

		bool operator==(const iterator& obj) const;
		bool operator!=(const iterator& obj) const;

		iterator* operator->();

	};

	void insert(iterator& itr_pos, const T value);
	void erase(iterator& itr_pos);

	iterator begin() const; // returns first
	iterator end() const; // returns nullptr

	~List();

};

// Link definitions

template <typename T>
Link<T>::Link(const T obj)
	: next{ nullptr }, prev{ nullptr }
{
	value = obj;
}

template <typename T>
Link<T>* Link<T>::operator->()
{
	return this;
}

template <typename T>
Link<T>::~Link()
{}

// List definitions

template <typename T>
List<T>::List(T obj) :
	size{ 0 }
{
	Link<T>* init = new Link<T>(obj);
	this->current_link = init;
	this->first = init;
	this->last = init;
}

template <typename T>
List<T>::List()
	: size{ 0 }, current_link{ nullptr }, first{ nullptr }, last{ nullptr }
{}

template <typename T>
List<T>::List(std::initializer_list<T> list_objs) // initialize as a list
	: size{ 0 }, current_link{ nullptr }, first{ nullptr }, last{ nullptr }
{
	auto itr = list_objs.begin();
	while (itr != list_objs.end())
	{
		this->push_back(*itr);
		++itr;
	}
}

template <typename T>
List<T>::List(const List<T>& list_obj)
	: size{ 0 }, current_link{ nullptr }, first{ nullptr }, last{ nullptr }
{
	iterator itr = list_obj.begin();
	while (itr != list_obj.end())
	{
		this->push_back(*itr);
		++itr;
	}
}

template <typename T>
List<T>::List(List<T>&& list_obj)
	: size{ 0 }, current_link{ nullptr }, first{ nullptr }, last{ nullptr }
{
	iterator itr = list_obj.begin();
	while (itr != list_obj.end())
	{
		this->push_back(std::move(*itr));
		++itr;
	}
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& list_obj)
{
	this->clear();

	iterator itr = list_obj.begin();
	while (itr != list_obj.end())
	{
		this->push_back(*itr);
		++itr;
	}

	return *this;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& list_obj)
{
	this->clear();

	iterator itr = list_obj.begin();
	while (itr != list_obj.end())
	{
		this->push_back(std::move(*itr));
		++itr;
	}

	return *this;
}

template <typename T>
void List<T>::push_back(T obj)
{
	Link<T>* temp = new Link<T>(obj);

	if (last)
	{
		temp->prev = this->last;
		this->last->next = temp;
	}

	this->last = temp;
	if (!this->first) this->first = temp;
	++this->size;

}

template <typename T>
void List<T>::push_front(T obj)
{
	Link<T>* temp = new Link<T>(obj);

	if (first)
	{
		temp->next = this->first;
		this->first->prev = temp;
	}

	this->first = temp;
	if (!this->last) this->last = temp;
	++this->size;
}

template <typename T>
void List<T>::pop_back()
{
	if (this->size <= 1) this->clear();
	else
	{
		Link<T>* new_last = last->prev;
		new_last->next = nullptr;

		delete this->last;
		this->last = new_last;
		
		--this->size;
	}
}	

template <typename T>
void List<T>::pop_front()
{
	if (this->size <= 1) this->clear();
	else
	{
		Link<T>* new_first = first->next;
		new_first->prev = nullptr;
		
		delete this->first;
		this->first = new_first;

		--this->size;	
	}
}

template <typename T>
T& List<T>::operator=(T obj)
{
	this->value = obj;
	return this->value;
}

template <typename T>
typename List<T>::iterator List<T>::begin() const
{
	List<T>::iterator itr(this->first);
	return itr;
}

template <typename T>
typename List<T>::iterator List<T>::end() const
{
	return nullptr; // todo: is this ok?
}

template <typename T>
bool List<T>::empty() const
{
	return (this->size == 0);
}

template <typename T>
void List<T>::clear()
{
	iterator itr = this->begin();
	Link<T>* ptr;
	while (itr != this->end())
	{
		ptr = itr->current;
		++itr;
		delete ptr;
	}

	size = 0;
	current_link = nullptr;
	first = nullptr;
	last = nullptr;
}

template <typename T>
List<T>::~List()
{
	this->clear();
}

template <typename T>
void List<T>::insert(List<T>::iterator& itr_pos, const T value)
{
	Link<T>* new_link = new Link<T>(value);
	Link<T>* prev_link = itr_pos->current->prev; // previous link

	if (prev_link)
	{
		prev_link->next = new_link;
		new_link->prev = prev_link;
	}

	new_link->next = itr_pos->current;
	itr_pos->current->prev = new_link;

	this->size++;
}

template <typename T>
void List<T>::erase(List<T>::iterator& itr_pos)
{
	if (itr_pos == this->first) this->pop_front();
	else if (itr_pos == this->last) this->pop_back();
	else
	{
		(itr_pos->current->prev)->next = itr_pos->current->next;
		(itr_pos->current->next)->prev = itr_pos->current->prev;

		delete itr_pos->current;
		--this->size;
	}
}


// List::iterator definitions


template <typename T>
List<T>::iterator::iterator(Link<T>* init_itr)
{
	this->current = init_itr;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
	this->current = this->current->next;
	return *this;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
	this->current = this->current->prev;
	return *this;
}

template <typename T>
T& List<T>::iterator::operator*()
{
	return this->current->value;
}

template <typename T>
bool List<T>::iterator::operator==(const iterator& obj) const
{
	return this->current == obj.current;
}

template <typename T>
bool List<T>::iterator::operator!=(const iterator& obj) const
{
	return this->current != obj.current;
}

template <typename T>
typename List<T>::iterator* List<T>::iterator::operator->()
{
	return this;
}

int main()
{
	List<int> var_list(1);

	var_list.push_back(2);
	var_list.push_back(3);
	var_list.push_back(4);
	var_list.push_front(0);


	List<int>::iterator itr = var_list.begin();
	while (itr != var_list.end())
	{
		std::cout << "\n" << *itr;
		++itr;
	}

	List<int> var_list2{};
	var_list2.push_back(1);
	var_list = var_list2;

	List<int> var_list3{ 99, 98, 97 };
	List<int>::iterator itr3 = var_list3.begin();
	while (itr3 != var_list3.end())
	{
		std::cout << "\n" << *itr3;
		++itr3;
	}

	itr3 = var_list3.begin();
	++itr3;

	var_list3.insert(itr3, 55555);
	var_list3.insert(itr3, 111);
	var_list3.insert(itr3, 123);

	std::cout << "printing list3" << std::endl;
	itr3 = var_list3.begin();
	while (itr3 != var_list3.end())
	{
		std::cout << "val is   " << *itr3 << std::endl;
		++itr3;
	}
	
	std::cout << "pop front and pop back list3" << std::endl;
	var_list3.pop_front();
	var_list3.pop_back();
	std::cout << "printing list3" << std::endl;
	itr3 = var_list3.begin();
	while (itr3 != var_list3.end())
	{
		std::cout << "val is   " << *itr3 << std::endl;
		++itr3;
	}
	std::cout << "erasing second element list3" << std::endl;
	var_list3.erase(++var_list3.begin());
	
	std::cout << "printing list3" << std::endl;
	itr3 = var_list3.begin();
	while (itr3 != var_list3.end())
	{
		std::cout << "val is   " << *itr3 << std::endl;
		++itr3;
	}

	return 0;
}
