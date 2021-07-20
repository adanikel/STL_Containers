#include <iostream>
#include <algorithm>
#include <cmath>
#include <initializer_list>


class Heap
{
	private:
		T* _elem_arr{ nullptr };
		static const unsigned int _DEF_SIZE{ 10 };
		static const unsigned int _DEF_EXT_VAL { 2 };
		unsigned int _capacity;		
		bool (*_sorting_algo)(T node_val, T parent_val); // pass ptr to overwrite this 

		T* _begin() const { return &this->_elem_arr[0]; };
		T* _end() const { return &this->_elem_arr[this->size]; };
		
		void _reallocate(); // when not enough space...
		void _swap(const unsigned int idx_1, const unsigned idx_2);
	
	public:
		unsigned int size;

		Heap(bool(*sort_mtd_ptr)(T, T));
		Heap(bool(*sort_mtd_ptr)(T, T), const std::initializer_list<T> lst);
		Heap(const Heap& src_heap);
		Heap(Heap&& rvalue_heap);

		Heap<T>& operator=(Heap<T>& heap_obj);
		Heap<T>& operator=(Heap<T>&& rvalue_heap);

		int get_parent_position(const unsigned int idx) const; // return array idx
		int get_right_child_position(const unsigned int idx) const; // return array idx
		int get_left_child_position(const unsigned int idx) const; // return array idx
		
		bool has_parent(const unsigned int idx) const;
		bool has_right_child(const unsigned int idx) const;
		bool has_left_child(const unsigned int idx) const;
	
		void insert(const T val); 
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
	
	std::cout << "copy const y, printing values" << std::endl;
	Heap<int> y{ x };
	idx = 0;
        while(idx < y.size)
        {
                std::cout << "elem of " << idx << " is " << y.get(idx) << std::endl;
                ++idx;
        }
	
	std::cout << "intializer list z" << std::endl;
	Heap<int> z(&is_bigger, std::initializer_list<int>{5, 8, 3, 6, 1, 9});
	z.sort_heap();
	idx = 0;
        while(idx < z.size)
        {
                std::cout << "elem of " << idx << " is " << z.get(idx) << std::endl;
                ++idx;
        }
	
	std::cout << "initializing heap a with rval" << std::endl;	
	Heap<int> a(Heap<int>(&is_bigger, std::initializer_list<int>{5, 8, 3, 6, 1, 9}));	
	a.sort_heap();
        idx = 0;
        while(idx < a.size)
        {
                std::cout << "elem of " << idx << " is " << a.get(idx) << std::endl;
                ++idx;
        }
	
	std::cout << "assigning heap a with x" << std::endl;
        a = x;
        a.sort_heap();
        idx = 0;
        while(idx < a.size)
        {
                std::cout << "elem of " << idx << " is " << a.get(idx) << std::endl;
                ++idx;
        }

	std::cout << "assigning heap a with rval" << std::endl;
        a = Heap<int>(&is_bigger, std::initializer_list<int>{5, 8, 3, 6, 1, 9});
        a.sort_heap();
        idx = 0;
        while(idx < a.size)
        {
                std::cout << "elem of " << idx << " is " << a.get(idx) << std::endl;
                ++idx;
        }

	return 0;
}

template <typename T>
Heap<T>::Heap(bool(*sort_mtd_ptr)(T, T))
	: _elem_arr{ new T[_DEF_SIZE] }, _capacity{ _DEF_SIZE }, size{ 0 }, _sorting_algo{ sort_mtd_ptr }
{}

template <typename T>
Heap<T>::Heap(bool(*sort_mtd_ptr)(T, T), const std::initializer_list<T> lst)
        : _elem_arr{ new T[static_cast<unsigned int>(lst.size())] }, _capacity{static_cast<unsigned int>(lst.size()) }, size{ 0 }, _sorting_algo{ sort_mtd_ptr }
{
	for(typename std::initializer_list<T>::iterator itr = lst.begin(); itr < lst.end(); itr++)
	{
		this->insert(*itr);
	}
}

template <typename T>
Heap<T>::Heap(const Heap& src_heap)
	: _elem_arr{ new T[src_heap._capacity] }, _capacity{ src_heap._capacity }, size{ src_heap.size }, _sorting_algo{ src_heap._sorting_algo }
{
	std::copy(src_heap._begin(), src_heap._end(), _elem_arr);
}

template <typename T>
Heap<T>::Heap(Heap&& rvalue_heap)
	: _elem_arr{ std::move(rvalue_heap._elem_arr) }, _capacity{ std::move(rvalue_heap._capacity) }, size{ std::move(rvalue_heap.size) }, _sorting_algo{ std::move(rvalue_heap._sorting_algo) }
{
	rvalue_heap._elem_arr = nullptr;
}

template <typename T>
Heap<T>& Heap<T>::operator=(Heap<T>& heap_obj)
{
	delete[] this->_elem_arr;
	this->_capacity = heap_obj._capacity;
	this->_elem_arr = new T[this->_capacity];
	std::copy(heap_obj._begin(), heap_obj._end(), this->_elem_arr);
	this->size = heap_obj.size;
	this->_sorting_algo = heap_obj._sorting_algo;
	
	return *this;
}

template <typename T>
Heap<T>& Heap<T>::operator=(Heap<T>&& rvalue_heap)
{
	delete[] this->_elem_arr;
        this->_capacity = std::move(rvalue_heap._capacity);
        this->_elem_arr = rvalue_heap._elem_arr;
        this->size = std::move(rvalue_heap.size);
        this->_sorting_algo = std::move(rvalue_heap._sorting_algo);
	
	rvalue_heap._elem_arr = nullptr;
	return *this;
}

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
