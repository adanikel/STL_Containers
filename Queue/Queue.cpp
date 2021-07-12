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
	iterator _last_index{ nullptr }; // will point to one after last element
	iterator _begin() const { return &(_elements[0]); };
	iterator _end() const { return &(_elements[_size]); }; // points to 1 after
public:
	Queue(unsigned int size); // not explicit - int and size_t are accepted
	explicit Queue(std::initializer_list<T> lst);
	Queue(Queue& src_queue); // copy constructor not const - to access iterator methods
	Queue(Queue&& r_queue) noexcept;

	Queue<T>& operator= (Queue<T>& queue_obj);
	Queue<T>& operator= (Queue<T>&& r_queue) noexcept;
	
	void enqueue(const T& val);
	void enqueue(T&& r_val);

	//T dequeue(); // not ref because deleting 
	
	bool is_full() const;
	bool is_empty() const { return {!this->_first_index && !this->_last_index}; };
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
	std::cout << "is x full VS is y full: " << x.is_full() << " " << y.is_full() << std::endl; // should be 0 1
	std::cout << "is x empty VS is y empty: " << x.is_empty() << " " << y.is_empty() << std::endl; // should be 1 0	
	std::cout << "enqueue 2 and 4&& to empty queue x " << std::endl;
	x.enqueue(2);
	x.enqueue(2 + 2);
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
	_last_index = &_elements[_size]; // todo: last one after? everywhere where required
}

template <typename T>
Queue<T>::Queue(Queue& src_queue)
	: _size{ src_queue.capacity() }, _elements{ new T[_size] }
{
	if (!src_queue.is_empty())  
        {
                unsigned int start_idx = src_queue._first_index - src_queue._begin();
                this->_first_index = &this->_elements[start_idx];
                for (T* itr = src_queue._first_index; itr != src_queue._last_index; itr++)
                {
                        this->_elements[start_idx] = *itr;
                        start_idx++;
                }      
                this->_last_index = &this->_elements[start_idx] + 1; // after we incremented it till first index
        }	
}

template <typename T>
Queue<T>::Queue(Queue&& r_queue) noexcept
	: _size{ r_queue.capacity() }, _elements{ new T[_size] }
{
	_elements = r_queue._elements; // snatch ptr
	r_queue._elements = nullptr; // nullify original to avoid deleting
	
	_first_index = &_elements[0];
	_last_index = &_elements[_size];
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>& queue_obj)
{
	delete[] _elements; // delete original queue
	this->_size = queue_obj.capacity();
	this->_elements = new T[this->_size];
	if (queue_obj.is_empty()) // nullify old values if existed
	{
		this->_first_index = nullptr;
		this->_last_index = nullptr;

	}
	else
	{
		unsigned int start_idx = queue_obj._first_index - queue_obj._begin();
		this->_first_index = &this->_elements[start_idx];
		for (T* itr = queue_obj._first_index; itr != queue_obj._last_index; itr++)
		{
			this->_elements[start_idx] = *itr;
			start_idx++;
		}
		
		this->_last_index = &this->_elements[start_idx + 1]; // after we incremented it till first index
	}
	return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& r_queue) noexcept
{
	delete[] _elements;
	this->_size = r_queue.capacity();
	this->_elements = r_queue._elements;
	
	if (r_queue.is_empty()) 
	{
		this->_first_index = nullptr;
		this->_last_index = nullptr;
	}
	else
	{
		unsigned int start_idx = r_queue._first_index - r_queue._begin();
		unsigned int num_of_elem = r_queue._last_index - r_queue._first_index;

		this->_first_index = &this->_elements[start_idx];
		this->_last_index = &this->_elements[start_idx + num_of_elem + 1];
	}
	r_queue._elements = nullptr;
	return *this;
}

template <typename T>
void Queue<T>::enqueue(const T& val)
{
	// todo define
	if (this->is_full()) std::cout << "cannot enqueue... queue is full" << std::endl;
	if (this->is_empty())
	{
		this->_last_index = this->_begin() + 1;
		this->_first_index = this->_begin();
		*this->_first_index = val;
	}
	else
	{
		*this->_last_index = val;
		this->_last_index++;
	}
}

template <typename T>
void Queue<T>::enqueue(T&& r_val)
{       
        // todo define
        if (this->is_full()) std::cout << "cannot enqueue... queue is full" << std::endl;
        if (this->is_empty())
        {       
                this->_last_index = this->_begin() + 1;
                this->_first_index = this->_begin();
                *this->_first_index = std::move(r_val);
        }
        else
        {       
                *this->_last_index = std::move(r_val);
                this->_last_index++;
        }
}

template <typename T>
bool Queue<T>::is_full() const
{
	return this->_last_index == this->_end() - 1; 
}

template <typename T>
Queue<T>::~Queue()
{
	delete[] _elements;
}

