#include <iostream>

template <typename T>
struct Link
{
	T* next = nullptr;
	T* prev = nullptr;
	T value;

	Link(T obj) { value = obj; };
	Link() {};

	~Link() { delete next; delete prev; };

};

template <typename T>
class List
{
private:
	Link<T>* current_link; // pointer to link. Value inside will not be through a pointer
	size_t size;

public:
	Link<T>* first;
	Link<T>* last;

	class iterator;

	List();
	List(T obj);

	T* push_back(T obj) { T temp = new Link<T>(obj); this->last = temp; this->size++; }; // todo: add as first index
	T* push_front(T obj) { T temp = new Link<T>(obj); this->first = temp; this->size++; };
	void forward() {};
	void backward() {};

	T& operator=(T obj) { this->value = obj;  return this->value; }

	~List() {};

};


template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list_obj)
{
	os << list_obj.current_link->value;
	return os;
}


template <typename T>
class List<T>::iterator
{
private:
	Link<T>* current;

public:

	iterator(List<T> init) { this->current = &init; }

	iterator& operator++() { current = current->next; return*this; }
	iterator& operator--() { current = current->prev; return *this; }
	T& operator*() { return current->value; }
	bool operator==(const iterator& obj) const { return current == obj.current; }
	bool operator!=(const iterator& obj) const { return current != obj.current; }

};

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
	size{ 0 }
{
	Link<T>* init = new Link<T>();
	this->current_link = init;
	this->first = init;
	this->last = init;
}


int main()
{
	List<int> var(45);
	return 0;
}
