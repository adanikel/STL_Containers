#include <iostream>
#include <initializer_list>

tempplate <typename T>
class Stack:
	private: 
		T* _elem_array{ nullptr };
		unsigned int _capacity;
		
		using iterator = T*;
		iterator _current{ nullptr };
		iterator _begin() { return &_elem_array[0]; };
		iterator _end() { return &_elem_array[_capacity]; };

	public:
		Stack();
		Stack(unsigned int sz);
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
