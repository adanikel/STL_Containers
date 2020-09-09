#include <iostream>


// Linked list
// todo: proper destructor


template <typename T>
struct Link
{
	T* next;
	T* prev;
	T value;

	explicit Link(const T obj); // no default constructor

	~Link();

};

template <typename T>
class List
{
private:
	Link<T>* current_link; // pointer to link. Value inside will not be through a pointer
	signed int size; // modify every addition / deletion

public:
	Link<T>* first;
	Link<T>* last;

	List(); // initialize all links as nullptr
	List(T obj);

	T* push_back(T obj); // todo: add as first index
	T* push_front(T obj);
	void forward() {};
	void backward() {};

	T& operator=(T obj);

	class iterator
	{
	private:
		Link<T>* current;

	public:

		iterator(List<T> init);

		T& operator*();

		iterator& operator++();
		iterator& operator--();

		bool operator==(const iterator& obj) const;
		bool operator!=(const iterator& obj) const;

	};

	~List() {};

};

// Link definitions

template <typename T>
Link<T>::Link(const T obj)
	: next{ nullptr }, prev{ nullptr }
{
	value = obj; 
};

template <typename T>
Link<T>::~Link()
{
	// todo: proper deletion
	delete next; 
	delete prev;
};

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
List<T>::List() :
	size{ 0 }, current_link{ nullptr }, first{ nullptr }, last{ nullptr }
{}

template <typename T>
T* List<T>::push_back(T obj)
{
	// todo: add next to index=size-1

	T temp = new Link<T>(obj); 
	this->last = temp; 
	this->size++; 
}

template <typename T>
T* List<T>::push_front(T obj) 
{
	// todo: add prev to index=0

	T temp = new Link<T>(obj);
	this->first = temp;
	this->size++; 
}

template <typename T>
T& List<T>::operator=(T obj) 
{
	this->value = obj; 
	return this->value;
}

// List::iterator definitions


template <typename T>
List<T>::iterator::iterator(List<T> init)
{
	this->current = &init; // todo: ?
}

template <typename T>
List<T>::iterator& List<T>::iterator::operator++() 
{
	this->current = this->current->next; 
	return*this;
}

template <typename T>
List<T>::iterator& List<T>::iterator::operator--()
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


int main()
{
	List<int> var(45);
	return 0;
}
