#include <iostream>
#include <algorithm>
#include <cmath>

// todo
// 1. passing array is not possible. consider passing ptr and size?
// 2. initialzier list
// 3. move and copy const
// 4. move and copy assignment
// 5. pass ptr to sort algo
// 6. remove top / bottom (instead of min max)

// todo docs
// 1. pass ptr address, make sure types are correct
// 2. min max as example for top child?
// 3. nodes idx return is -1 if doesnt exist

template <typename T>
class Heap
{
	private:
		T* _elem_arr{ nullptr };
		static const unsigned int _DEF_SIZE{ 10 };
		static const unsigned int _DEF_EXT_VAL { 2 };
		unsigned int _capacity;		
		unsigned int _size;

		T* _begin() const { return &this->_elem_arr[0]; };
		T* _end() const { return &this->_elem_arr[this->_size]; };
		
		void _reallocate(); // when not enough space...
		
		bool (*_sorting_algo)(T node_val, T parent_val); // pass ptr to overwrite this 
		
		void _swap(const unsigned int idx_1, const unsigned idx_2);
	
	public:
		Heap(bool(*sort_mtd_ptr)(T, T));

		int get_parent_position(const unsigned int idx) const; // return array idx
		int get_right_child_position(const unsigned int idx) const; // return array idx
		int get_left_child_position(const unsigned int idx) const; // return array idx
		
		bool has_parent(const unsigned int idx) const;
		bool has_right_child(const unsigned int idx) const;
		bool has_left_child(const unsigned int idx) const;
	
		Heap(bool(*sort_mtd_ptr)(T, T));
		
		void insert(const T val); // TODO return node #??
		
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
	: _elem_arr{ new T[_DEF_SIZE] }, _capacity{ _DEF_SIZE }, _size{ _DEF_SIZE }, _sorting_algo{ sort_mtd_ptr }
{
	std::cout << this->_sorting_algo(2, 3) << std::endl << this->_sorting_algo(3, 2) << std::endl; // TODO remove
	std::cout << this->_get_parent_position(3) << std::endl; // should be 1
}

template <typename T>
void Heap<T>::_reallocate()
{
	this->_capacity *= this->_DEF_EXT_VAL;
	T* new_arr = new T[this->_capacity];
	std::move(this->_begin(), this->_end() - 1, new_arr);
	
	delete[] this->_elem_arr;
	this->_elem_arr = new_arr; 
}

template <typename T>
void Heap<T>::_swap(const unsigned int idx_1, const unsigned int idx_2) 
{
	std::swap(this->_elem_arr[idx_1], this->_elem_arr[idx_2]);
}

template <typename T>
int Heap<T>::get_parent_position(const unsigned int idx) const
{
	return this->has_parent(idx) ? std::floor((idx - 1) / 2) : -1;
}

template <typename T>
int Heap<T>::get_right_child_position(const unsigned int idx) const
{
	return this->has_right_child(idx) ? (2 * idx) + 2 : -1;
}

template <typename T>
int Heap<T>::get_left_child_position(const unsigned int idx) const
{
	return this->has_left_child(idx) ? (2 * idx) + 1 : -1;
}

template <typename T>
bool Heap<T>::_has_parent(const unsigned int idx) const
{
	return idx != 0;
}

template <typename T>
bool Heap<T>::_has_right_child(const unsigned int idx) const
{
	this->_get_right_child_position(idx) < this->_size;
}

template <typename T>
bool Heap<T>::_has_left_child(const unsigned int idx) const
{
	return this->_get_left_child_position(idx) < this->_size;
}

template <typename T>
void Heap<T>::insert(const T val)
{
	this->_elem_arr[this->_size] = val;
}

template <typename T>
Heap<T>::~Heap()
{
	delete[] this->_elem_arr;
}
