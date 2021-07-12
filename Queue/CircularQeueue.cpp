#include "Queue.cpp"
#include <initializer_list>

// this class simply derives from Queue and adds the ability to be circular
// todo: 
// 1. define enqeuee
// 2. define enqueue rval
// 3. define deqeuu
// 4. take care of main_2e

template <typename T>
class CircularQueue : public Queue<T>
{
	private:
		unsigned int _elem_count{ 0 }; // keep track of how many elements are currently in the queue
	public:
	       	// constructors - merely super to Queue class
		CircularQueue(unsigned int size) : Queue<T>(size) {}; 
		explicit CircularQueue(std::initializer_list<T> lst) : Queue<T>(lst) {};
		CircularQueue(CircularQueue& src_queue) : Queue<T>(src_queue) {}; 
		CircularQueue(CircularQueue&& r_queue) noexcept : Queue<T>(std::move(r_queue)) {};
		
		bool is_full() const; // overwwrite is_full
		
		void enqueue(const T& val);
		void enqueue(T&& r_val);

		T dequeue();

		unsigned int get_size() const { return this->_elem_count(); }; // can't be last - first as in the regular Queue
};
int main()
{
	CircularQueue<int> d(std::initializer_list<int>{40, 50, 60});
	std::cout << " is d full? " << d.is_full() << std::endl;
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
	if (this->_is_full()) throw; // don't override old values
	else
	{
		if (this->is_empty())
		{
			this->_last_index = this->_begin() + 1;
		        this->_first_index = this->_begin();
			*this->_first_index = val
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
	if (this->_is_full()) throw; 
        else
	{
		if (this->is_empty())
		{
			this->_last_index = this->_begin() + 1;
			this->_first_index = this->_begin();
			*this->_first_index = std::move(val)
		}
		else
		{
			if (this->_last_index == this->_end())
			{
				this->_last_index = this->_begin() 
				*this->_begin() = std::move(val);
			}
			else
			{
			*this->_last_index = std::move(val);
	                this->_last_index++;
			}
		}
		++this->_elem_count;
	}
}

template <typename T>
T CircularQueue<T>::dequeue()
{

}
