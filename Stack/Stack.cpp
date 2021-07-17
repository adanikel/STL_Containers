#include <iostream>
#include <initializer_list>

template <typename T>
class Stack
{
	private: 
		T* _elem_array{ nullptr };
		unsigned int _capacity;
		static const unsigned int _DEF_CAP{ 10 };
		
		using iterator = T*;
		iterator _current{ nullptr }; // one past last
		iterator _begin() const { return &_elem_array[0]; };
		iterator _end() const { return &_elem_array[_capacity]; };

	public:
		Stack(unsigned int sz = _DEF_CAP);
		Stack(std::initializer_list<T> lst);
		
		Stack(const Stack<T>& stack_obj);
		Stack(Stack<T>&& stack_rval);
		
		Stack<T>& operator=(const Stack<T>& stack_obj);
		Stack<T>& operator=(Stack<T>&& stack_rval);
		
		bool is_empty() const { return this->_current == this->_begin(); };
		bool is_full() const { return this->_current == this->_end(); };
		
		void push(const T val);
		T pop();

		~Stack();

};

int main()
{
	Stack<int> a = Stack<int>();
	a.push(2);
	a.push(8);
	std::cout << a.pop() << std::endl;
        std::cout << a.pop() << std::endl;
	a.push(7);
	std::cout << a.pop() << std::endl;
	a.push(2);

	Stack<int> b = Stack<int>(9);
	b = a;
	std::cout << b.pop() << std::endl;
			
	return 0;
}

template <typename T> 
Stack<T>::Stack(unsigned int sz)
	: _capacity{ sz }, _elem_array{ new T[sz] }, _current{ _begin() }
{}

template <typename T>
Stack<T>::Stack(std::initializer_list<T> lst)
	: _capacity{ lst.size() }, _elem_array{ new T[lst.size()] }, _current{ _begin() }
{
        for (typename std::initializer_list<T>::iterator itr = lst.begin(); itr != lst.end(); itr++)
        {
                push(*itr);
        }
}

template <typename T>
Stack<T>::Stack(const Stack<T>& stack_obj)
	: _capacity{ stack_obj._capacity }, _elem_array{ new T[stack_obj._capacity] }, _current{ _begin() }
{
	if (!stack_obj.is_empty())
	{
		for (Stack<T>::iterator itr = stack_obj._begin(); itr != stack_obj._current; itr++)
		{
			push(*itr);
		}
	}
}

template <typename T>
Stack<T>::Stack(Stack<T>&& stack_rval)
	: _capacity{ std::move(stack_rval._capacity) }, _elem_array{ std::move(stack_rval._elem_array) }, _current{ std::move(stack_rval._current) }
{
	stack_rval._elem_array = nullptr;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack_obj)
{
	delete[] this->_elem_array;

        this->_capacity = stack_obj._capacity;
        this->_elem_array = new T[this->_capacity];
	
	if (!stack_obj.is_empty())
	{
        	for (Stack<T>::iterator itr = stack_obj._begin(); itr != stack_obj._current; itr++)
        	{
                	this->push(*itr);
        	}
	}
        
	return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& stack_rval)
{
	delete[] this->_elem_array;
        this->_capacity = std::move(stack_rval._capacity);
        this->_elem_array = std::move(stack_rval._elem_array);
	this->_current = std::move(stack_rval._current);

	stack_rval._elem_array = nullptr;
        
	return *this;
}

template <typename T>
void Stack<T>::push(const T val)
{
	if (this->is_full()) throw;
	else
	{
		*this->_current = val;
		this->_current++;
	}
}

template <typename T>
T Stack<T>::pop()
{
	if (this->is_empty()) throw;
	else
	{
		return *(--this->_current);
	}
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] this->_elem_array;
}
