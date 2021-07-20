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
// 4. order of traversal

template <typename T>
class Heap
{
	private:
		T* _elem_arr{ nullptr };
		static const unsigned int _DEF_SIZE{ 10 };
		static const unsigned int _DEF_EXT_VAL { 2 };
		unsigned int _capacity;		

		T* _begin() const { return &this->_elem_arr[0]; };
		T* _end() const { return &this->_elem_arr[this->size]; };
		
		void _reallocate(); // when not enough space...
		
		bool (*_sorting_algo)(T node_val, T parent_val); // pass ptr to overwrite this 
	
		void _swap(const unsigned int idx_1, const unsigned idx_2);
	
	public:
		unsigned int size;

		Heap(bool(*sort_mtd_ptr)(T, T));

		int get_parent_position(const unsigned int idx) const; // return array idx
		int get_right_child_position(const unsigned int idx) const; // return array idx
		int get_left_child_position(const unsigned int idx) const; // return array idx
		
		bool has_parent(const unsigned int idx) const;
		bool has_right_child(const unsigned int idx) const;
		bool has_left_child(const unsigned int idx) const;
	
		void insert(const T val); // TODO return node #??
		T& get(const unsigned int idx); // get val in certain index
		unsigned int heapify(unsigned int idx); // returns new index 
		void sort_heap();
			
		~Heap();
};

bool is_bigger(int val_1, int val_2)
{
	return val_1 > val_2;
}

int main()
{
	Heap<int> x{&is_bigger};
	x.insert(1);
        x.insert(4);
        x.insert(3);
        x.insert(7);
        x.insert(8);
        x.insert(9);
	x.insert(0);
	x.insert(11);
	x.insert(939);
	x.insert(44);
	x.insert(8547);
	x.insert(15);
        x.insert(10);
	x.sort_heap();

	unsigned int idx{ 0 };
	while(idx < x.size)
	{
		std::cout << "elem of " << idx << " is " << x.get(idx) << std::endl;	
		++idx;
	}
	return 0;
}

template <typename T>
Heap<T>::Heap(bool(*sort_mtd_ptr)(T, T))
	: _elem_arr{ new T[_DEF_SIZE] }, _capacity{ _DEF_SIZE }, size{ 0 }, _sorting_algo{ sort_mtd_ptr }
{}

template <typename T>
void Heap<T>::_reallocate()
{
	this->_capacity *= this->_DEF_EXT_VAL;
	T* new_arr = new T[this->_capacity];
	std::move(this->_begin(), this->_end(), new_arr);
	
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
bool Heap<T>::has_parent(const unsigned int idx) const
{
	return idx != 0;
}

template <typename T>
bool Heap<T>::has_right_child(const unsigned int idx) const
{
	this->get_right_child_position(idx) < this->size;
}

template <typename T>
bool Heap<T>::has_left_child(const unsigned int idx) const
{
	return this->get_left_child_position(idx) < this->size;
}

template <typename T>
void Heap<T>::insert(const T val)
{	
	if (this->size == this->_capacity) this->_reallocate();
	this->_elem_arr[this->size] = val;
	++this->size;
}

template <typename T>
T& Heap<T>::get(const unsigned int idx)
{
	return this->_elem_arr[idx];
}

template <typename T>
unsigned int Heap<T>::heapify(unsigned int idx)
{
	while (this->has_parent(idx) && this->_sorting_algo(this->_elem_arr[idx], this->_elem_arr[this->get_parent_position(idx)]))
	{	
		this->_swap(idx, this->get_parent_position(idx));
		idx = this->get_parent_position(idx);
	}
	return idx;
}

template <typename T>
void Heap<T>::sort_heap()
{
	unsigned int idx{ 0 };
	while(idx < this->size)
	{
		this->heapify(idx);
		++idx;
	}
}

template <typename T>
Heap<T>::~Heap()
{
	delete[] this->_elem_arr;
}
