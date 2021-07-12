#include "Queue.cpp"
#include <initializer_list>

// this class simply derives from Queue and adds the ability to be circular
// todo: 
// 1. define enqeuee
// 2. define enqueue rval
// 3. define deqeuue

template <typename T>
class CircularQueue : public Queue<T>
{
	public:
	       	// constructors - merely super to Queue class
		CircularQueue(unsigned int size) : Queue<T>(size) {}; 
		explicit CircularQueue(std::initializer_list<T> lst) : Queue<T>(lst) {};
		CircularQueue(CircularQueue& src_queue) : Queue<T>(src_queue) {}; 
		CircularQueue(CircularQueue&& r_queue) noexcept : Queue<T>(std::move(r_queue)) {};
		
		bool is_full() const; // overwwrite is_full
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
	return (this->_last_index == this->_end()) && (this->_first_index == this->_begin());
}
