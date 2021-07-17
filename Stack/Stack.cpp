#include <iostream>
#include <initializer_list>

tempplate <typename T>
class Stack:
{
	private: 
		T* _elem_array{ nullptr };
		unsigned int _capacity;
		unsigned int _DEF_CAP{ 10 };
		
		using iterator = T*;
		iterator _current{ nullptr }; // one past last
		iterator _begin() { return &_elem_array[0]; };
		iterator _end() { return &_elem_array[_capacity]; };

	public:
		Stack(unsigned int sz = _DEF_CAP);
		Stack(std::initializer_list<T> lst);
		
		Stack(const Stack<T>& stack_obj);
		Stack(Stack<T>&& stack_rval);
		
		Stack<T>& operator=(const Stack<T>& stack_obj);
		Stack<T>& operator=(Stack<T>&& stack_rval);
		
		bool is_empty() const; { return this->_current == this->_begin(); };
		bool is_full() const; { return this->_current == this->end(); };
		
		void push(const T val);
		T pop();

		~Stack();

}

int main()
{
	Stack<int> a;
	
	return 0;
}

template <typename T> 
Stack<T>::Stack(unsigned int sz)
	: _capacity{ sz }, _elem_array{ new T[_capacity] }, _current{ _begin() }
{}

template <typename T>
Stack<T>::Stack(std::initializer_list<T> lst)
	: _capacity{ lst.size() }, _elem_array{ new T[_capacity] }, _current{ _begin() }
{
        for (std::initializer_list<T>::iterator itr = lst.begin(); itr != lst.end(); itr++)
        {
                push(*itr);
        }
}

template <typename T>
Stack<T>::Stack(const Stack<T>& stack_obj)
	: _capacity{ stack_obj.capacity() }, _elem_array{ new T[_capcity] }, _current { _begin() }
{
	for (Stack<T>::iterator itr stack_obj.begin(); itr != stack_obj.end(); itr++)
	{
		push(*itr);
		current++;
	}
}

template <typename T>
Stack<T>::Stack(Stack<T>&& stack_rval)
	: _capcity{ std::move(stack_rval._capacity) }, _elem_array{ std::move(stack_rval._elem_array }, _current{ std::move(stack_rval._current) }
{
	stack_rval._capcity = nullptr;
	stack_rval._elem_array = nullptr;
	stack_rval._current = nullptr;
}
