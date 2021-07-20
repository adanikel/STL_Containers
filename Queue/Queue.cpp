#include <initializer_list>
#include <iostream>

// an implementation of a basic queue data structure

template <typename T>
class Queue
{
protected:
	unsigned int _size;
	T* _elements{ nullptr };
	void _reset_indices();
	void _cpy_elements(const Queue& other_queue);

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

	Queue<T>& operator=(Queue<T>& queue_obj);
	Queue<T>& operator=(Queue<T>&& r_queue) noexcept;
	
	virtual void enqueue(const T& val);
	virtual void enqueue(T&& r_val);

	virtual T dequeue(); // not ref because deleting 
	
	virtual bool is_full() const;
	bool is_empty() const { return {!this->_first_index && !this->_last_index}; };
	unsigned int capacity() const { return _size; };
	virtual unsigned int get_size() const; // return number of elements...	
	
	~Queue(); // deallocate memory
	
};

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
		this->_cpy_elements(src_queue);
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
		this->_reset_indices();
	}
	else
	{
		this->_cpy_elements(queue_obj);	
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
		this->_reset_indices();
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
	if (this->is_full()) throw;
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
        if (this->is_full()) throw; 
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
T Queue<T>::dequeue()
{
	if (!this->is_empty())
	{
		T val = *this->_first_index;
		if ((++this->_first_index) == this->_end())
		{
			this->_reset_indices();
		}
		
		return val;
	}
	else
	{
		throw;
	}
}

template <typename T>
bool Queue<T>::is_full() const
{
	return this->_last_index == this->_end(); 
}

template <typename T>
unsigned int Queue<T>::get_size() const
{ 
	return 0 ? this->is_empty() : this->_last_index - this->_first_index; 
};

template <typename T>
void Queue<T>::_reset_indices()
{
	this->_first_index = nullptr;
	this->_last_index = nullptr;	
}

template <typename T>
void Queue<T>::_cpy_elements(const Queue& other_queue)
{
	unsigned int start_idx = other_queue._first_index - other_queue._begin();
        this->_first_index = &this->_elements[start_idx];
        for (T* itr = other_queue._first_index; itr != other_queue._last_index; itr++)
        {       
                this->_elements[start_idx] = *itr;
                start_idx++;
        }
             
	this->_last_index = &this->_elements[start_idx + 1]; // after we incremented it till first index	
}

template <typename T>
Queue<T>::~Queue()
{
	delete[] _elements;
}

