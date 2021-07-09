#include <initializer_list>
#include <iostream>

// an implementation of a basic queue data structure

template <typename T>
class Queue
{
private:
	unsigned int _size;
	T* _elements{ nullptr };

	using iterator = T*;
	iterator _first_index{ nullptr };
	iterator _last_index{ nullptr };
	iterator _begin() { return &(_elements[0]); };
	iterator _end() { return &(_elements[_size]); };
public:
	Queue(unsigned int size); // not explicit - int and size_t are accepted
	explicit Queue(std::initializer_list<T> lst);
	Queue(Queue& src_queue); // copy constructor not const - to access iterator methods
	Queue(Queue&& r_queue) noexcept;

	Queue<T>& operator= (Queue<T>& queue_obj);
	Queue<T>& operator= (Queue<T>&& r_queue) noexcept;
	
	//void enqueue(const T& val);
	//void enqueue(T&& r_val);

	//T dequeue(); // not ref because deleting 
	
	unsigned int capacity() const { return _size; };
	//unsigned int getsize() const; // return number of elements...	
	
	~Queue(); // deallocate memory
	
};

int main()
{
	Queue<int> x( 4 );
	Queue<int> y(std::initializer_list<int>{1, 2, 3, 4, 5}); // construct with initializer list
	Queue<int> z(y);

	Queue<int> a( Queue<int>(std::initializer_list<int>{4, 5, 6}) );
	
	a = y;
	std::cout << "a = y and a's capcity is: " << a.capacity() << std::endl;
	std::cout<< "a vs y memory locations " << &a << " " << &y << std::endl;
	a = Queue<int>(std::initializer_list<int>{8, 7, 6});
	std::cout << "a = rvalue(new queue) and its capacity is " << a.capacity() << std::endl;
	return 0;
}

template <typename T>
Queue<T>::Queue(unsigned int size)
	: _size{ size }, _elements{ new T[_size] }
{}

template <typename T>
Queue<T>::Queue(std::initializer_list<T> lst)
	: _size{ static_cast<unsigned int>(lst.size()) }, _elements{ new T[_size] } // static_cast from size_t to avoid warnings
{
	unsigned int elem_idx{ 0 };
	for (auto lst_itr = lst.begin(); lst_itr != lst.end(); lst_itr++)
	{
		_elements[elem_idx] = *(lst_itr);
		elem_idx++;
	}

	_first_index = &_elements[0];
	_last_index = &_elements[_size - 1];
}

template <typename T>
Queue<T>::Queue(Queue& src_queue)
	: _size{ src_queue.capacity() }, _elements{ new T[_size] }
{
	unsigned int elem_idx{ 0 };
	for(T* itr = src_queue._begin(); itr != src_queue._end(); itr++)
	{
		_elements[elem_idx] = *(itr);
		elem_idx++;
	}

	_first_index = &_elements[0];
       _last_index = &_elements[_size - 1];	
}

template <typename T>
Queue<T>::Queue(Queue&& r_queue) noexcept
	: _size{ r_queue.capacity() }, _elements{ new T[_size] }
{
	_elements = r_queue._elements; // snatch ptr
	r_queue._elements = nullptr; // nullify original to avoid deleting
	
	_first_index = &_elements[0];
	_last_index = &_elements[_size - 1];
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>& queue_obj)
{
	delete[] _elements; // delete original queue
	this->_size = queue_obj.capacity();
	this->_elements = new T[this->_size];

	unsigned int elem_idx{ 0 };
	for (T* itr = queue_obj._begin(); itr != queue_obj._end(); itr++)
	{
		this->_elements[elem_idx] = *itr;
	}
	return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& r_queue) noexcept
{
	delete[] _elements;
	this->_size = r_queue.capacity();
	this->_elements = r_queue._elements;

	r_queue._elements = nullptr;
	return *this;

}

template <typename T>
Queue<T>::~Queue()
{
	delete[] _elements;
}

