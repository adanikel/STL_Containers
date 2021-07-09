#include <initializer_list>
#include <iostream>

// an implementation of a basic queue data structure

template <typename T>
class Queue
{
private:
	unsigned int _size;
	using iterator = T*;
	iterator _begin();
	iterator _end();
public:
	Queue(unsigned int size); // not explicit - int and size_t are accepted
	explicit Queue(std::initializer_list<T> lst);
	Queue(Queue& src_queue);
	Queue(Queue&& r_queue) noexcept;

	T& operator= (Queue<T>& queue);
	T&& operator= (Queue<T>&& r_queue);

	
};

int main()
{
	Queue<int> x = Queue();
}

Queue()


