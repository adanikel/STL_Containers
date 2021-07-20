#include <iostream>

// todo
// 1. passing array is not possible. consider passing ptr and size?
// 2. initialzier list
// 3. move and copy const
// 4. move and copy assignment
// 5. pass ptr to sort algo
// 6. remove top / bottom (instead of min max)

template <typename T>
class Heap
{
	private:
		T* _elem_arr{ nullptr };
		static const unsigned int _DEF_SIZE{ 10 };		
		unsigned int _size;

		T* _begin() const { return &this->_elem_arr[0]; };
		T* _end() const { return &this->_elem_arr[this->_size]; };
		
		void _reallocate(); // when not enough space...
		
		bool (*_sorting_algo)(T node_val, T parent_val); // pass ptr to overwrite this 
		
	public:
		Heap(bool(*sort_mtd_ptr)(T, T));
		
		unsigned int insert(T val);
		
		~Heap();
};

bool is_bigger(int val_1, int val_2)
{
	return val_1 > val_2;
}

int main()
{
	Heap<int> x{&is_bigger};

	return 0;
}

template <typename T>
Heap<T>::Heap(bool(*sort_mtd_ptr)(T, T))
	: _elem_arr{ new T[_DEF_SIZE] }, _size{ _DEF_SIZE } 
{
	this->_sorting_algo = sort_mtd_ptr;
	std::cout << this->_sorting_algo(2, 3) << std::endl << this->_sorting_algo(3, 2) << std::endl; // TODO remove
}

template <typename T>
void Heap<T>::_reallocate()
{
	this->_size *= 2;
	T* new_arr = new T[this->_size];
	std::move(this->_begin(), this->_end() - 1, new_arr);
	
	delete[] this->_elem_arr;
	this->_elem_arr = new_arr; 
}

template <typename T>
Heap<T>::~Heap()
{
	delete[] this->_elem_arr;
}
