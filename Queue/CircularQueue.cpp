#include "Queue.cpp"
#include <initializer_list>

template <typename T>
class CircularQueue : public Queue<T>
{
	private:
		unsigned int _elem_count{ 0 }; // keep track of how many elements are currently in the queue
	public:
	       	// constructors - merely super to Queue class
		CircularQueue(unsigned int size) : Queue<T>(size) { _elem_count = size; }; 
		explicit CircularQueue(std::initializer_list<T> lst) : Queue<T>(lst), _elem_count{ static_cast<unsigned int>(lst.size()) } {};
		CircularQueue(CircularQueue& src_queue) : Queue<T>(src_queue), _elem_count{ src_queue.get_size() } {}; 
		CircularQueue(CircularQueue&& r_queue) noexcept : Queue<T>(std::move(r_queue)), _elem_count{ r_queue.get_size() } {};
		
		bool is_full() const; // overwwrite is_full
		
		void enqueue(const T& val);
		void enqueue(T&& r_val);

		T dequeue();

		unsigned int get_size() const { return this->_elem_count; }; // can't be last - first as in the regular Queue
};

int main()
{
	CircularQueue<int> d(std::initializer_list<int>{40, 50, 60});
	std::cout << " is d full? " << d.is_full() << std::endl;
	std::cout << " d size is " << d.get_size() << std::endl;
	std::cout << "dequeue one and enqueue 70 " << std::endl;
	std::cout << " d size is " << d.get_size() << " and the dequeue value is " << d.dequeue() << std::endl;
	d.enqueue(70);
	
	unsigned int elems = d.get_size();
	while (elems)
	{
		std::cout << d.dequeue() << std::endl;
		elems--;
	}

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
	std::cout << "dequeue from x: " << x.dequeue() << std::endl;
	std::cout << "dequeue from x again: " << x.dequeue() << std::endl;
	
	return 0;
}

template <typename T>
bool CircularQueue<T>::is_full() const
{
	return (this->_elem_count == this->_size);
}

template <typename T>
void CircularQueue<T>::enqueue(const T& val)
{
	if (this->is_full()) throw; // don't override old values
	else
	{
		if (this->is_empty())
		{
			this->_last_index = this->_begin() + 1;
		        this->_first_index = this->_begin();
			*this->_first_index = val;
		}
		else // todo: circular here
		{
			if (this->_last_index == this->_end())
			{
				this->_last_index = this->_begin() + 1;
				*this->_begin() = val;  // set first as val
			}
			else
			{
				*this->_last_index = val;
				this->_last_index++;
			}
		}
		++this->_elem_count;
	}	
}

template <typename T>
void CircularQueue<T>::enqueue(T&& r_val)
{
	if (this->is_full()) throw; 
        else
	{
		if (this->is_empty())
		{
			this->_last_index = this->_begin() + 1;
			this->_first_index = this->_begin();
			*this->_first_index = std::move(r_val);
		}
		else
		{
			if (this->_last_index == this->_end())
			{
				this->_last_index = this->_begin(); 
				*this->_begin() = std::move(r_val);
			}
			else
			{
			*this->_last_index = std::move(r_val);
	                this->_last_index++;
			}
		}
		++this->_elem_count;
	}
}

template <typename T>
T CircularQueue<T>::dequeue()
{
	if (!this->is_empty())
	{
		T val = *this->_first_index;
		--this->_elem_count;
		if (this->_elem_count) // TODO define... if got here then: queue is not empty, and is also not empty after the "--" 
		{
			this->_first_index = this->_first_index + 1  < this->_end() ? this->_first_index + 1 : this->_begin(); // TODO what is last element was dequeued
		}
		else // TODO queue is not empty but has zero elements?
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

