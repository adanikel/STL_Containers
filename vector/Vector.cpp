#include <initializer_list>
#include <stdexcept>  // for out of range
#include <algorithm> // for std::copy
#include <iostream>

// an implementation of vector using dynamic memory and arrays

template <typename T>
class Vec
{
private:
	unsigned int _space; // available space
	const unsigned int _DEF_EXT_VAL{ 2 }; // default value to array memory realocation for extending 

public:
	unsigned int sz; // size of array
	T* elem{ nullptr }; // will be the array, initialized as null pointer

	Vec(unsigned int inp1); // not explicit intentionally (int and size_t are acceptable)
	explicit Vec(std::initializer_list<T> lst); // to user 'Vec{a, b, c}'
	Vec(const Vec& src_vec); // copy constructor
	Vec(Vec&& rvalue_vec) noexcept; // move constructor

	Vec<T>& operator= (const Vec<T>& obj); // redefining = operator
	Vec<T>& operator= (Vec<T>&& obj) noexcept; // redefining = operator for rvalue
	T& operator[] (const int index); // redefining [] operator
	T operator[] (const int index) const; // redefining [] operator for constant!! does not return a reference!!

	using iterator = T*;
	iterator begin() { return &(elem[0]); } // pointer to first element
	iterator end() { return &elem[sz]; } // pointer to last element
	iterator insert(iterator plc, const T obj); // insert new objects
	void erase(iterator plc); // erase existing objects

	void set(const unsigned int pos, T obj); // checks for out of range error unlike [] operators
	T get(int pos); // checks for out of range error unlike [] operators
	T& at(const int pos); // checks for out of range error unlike [] operators

	void push_back(T obj); // append element to top of vector
	void pop_back();  // remove last element

	unsigned int get_size() const { return sz; }; // get size of vector
	unsigned int get_elemsize() const { return sizeof(T); }; // get size of element
	inline bool empty() { return (sz == 0); };

	inline unsigned int capacity() { return _space; }; // get size of underlying element array
	iterator reserve(unsigned int new_space); // reserve new space for array

	~Vec(); // deallocate memory; another alternative is to use a unique_ptr
};

int main()
{
	Vec<int> var(5);
	var.set(0, 0);

	var[1] = 1;
	var[2] = 2;
	var[3] = 3;
	var[4] = 4;
	var[8] = 8; // works but illustrates how this should not be done... undefined behaviour! use set()

	Vec<int>::iterator itr;
	itr = var.begin();
	std::cout << "will insert soon" << std::endl;
	std::cout << "old size is " << var.get_size() << std::endl;

	for (unsigned int idx = 0; idx != var.sz; idx++)	
	{	
		std::cout << var[idx] << std::endl;
	};
	var.insert(itr + 1, 999);
	var.pop_back();
	std::cout << "inserted 999 as first index and popped back" << std::endl;
	for (unsigned int idx = 0; idx != var.sz; idx++)
	{
		std::cout << var[idx] << std::endl;
	};
	std::cout << "now erase first and last (last using erase)" << std::endl;
	var.erase(itr);
	var.erase(var.end() - 1);
	for (unsigned int idx = 0; idx != var.sz; idx++)
	{
		std::cout << var[idx] << std::endl;
	};
	std::cout << "new size is " << var.get_size() << std::endl;
	std::cout << "reserving new space... old capacity is " << var.capacity() << std::endl;
	var.reserve(2 * var.capacity());
	std::cout << "reserved, new capacity is " << var.capacity() << std::endl;
	
	std::cout << "testing copy const" << std::endl;
	Vec<int> var2{ var };
	return 0;
}


template <typename T>
Vec<T>::Vec(const unsigned int inp1)
	:sz{ inp1 }, _space{ inp1 * 2 }, elem{ new T[_space] }
{}

template <typename T>
Vec<T>::Vec(std::initializer_list<T> lst) 
	: sz{ lst.size() }, _space{ lst.size() * _DEF_EXT_VAL }, elem{ new T[_space] }
{
	auto lst_itr = lst.begin();
	for (unsigned int idx = 0; idx != sz; idx++) 
	{
		this->elem[idx] = *(lst_itr);
		lst_itr++;
	}
}

template <typename T>
Vec<T>::Vec(const Vec& src_vec) 
	:sz{ src_vec.sz }, _space{ src_vec._space }, elem{ new T[_space] }
{
	std::copy(src_vec.elem, src_vec.elem + sz, this->elem);

}

template <typename T>
Vec<T>::Vec(Vec<T>&& rvalue_vec) noexcept
	:sz{ rvalue_vec.sz }, _space{ rvalue_vec._space }
{
	this->elem = rvalue_vec.elem; // snatch pointer
	rvalue_vec.elem = nullptr; // nullify rvalue elem pointer

}

template <typename T>
void Vec<T>::erase(Vec<T>::iterator plc)
{
	if (plc == this->end() - 1)
	{
		this->pop_back();
	}
	else
	{
		for (iterator temp = plc; temp != this->end() - 1; temp++)
		{
			*temp = *(temp + 1);
		};
	--this->sz;
	}
}

template <typename T>
typename Vec<T>::iterator Vec<T>::insert(Vec<T>::iterator plc, const T obj)
{
	unsigned int loc = plc - this->begin(); // might be invalidated if 'reserve' is called, and therefore I save the location
	if (!(this->sz + 1 < this->_space)) this->reserve(sz * this->_DEF_EXT_VAL);
	plc = this->begin() + loc;

	for (iterator temp = this->end(); temp != plc; temp--) 
	{
		*temp = *(temp - 1);
	};

	*plc = obj;

	++this->sz;

	return plc;
}


template <typename T>
Vec<T>& Vec<T>::operator= (const Vec<T>& obj) // copy
{
	delete[] elem;

	this->sz = obj.sz;
	elem = new T[this->sz];

	for (unsigned int index = 0; index != obj.sz; index++)
	{
		this->elem[index] = obj[index];
	}

	return *this;
}

template <typename T>
Vec<T>& Vec<T>::operator= (Vec<T>&& obj) noexcept
{
	delete[] this->elem; 
	this->sz = obj.sz;
	this->_space = obj._space;

	elem = obj.elem; // snatch pointer from origin
	obj.elem = nullptr; // nullify origin pointer

	return *this;
}

template <typename T>
T Vec<T>::operator[] (const int index) const
{
	return this->elem[index];
}

template <typename T>
T& Vec<T>::operator[] (const int index)
{
	return this->elem[index];
}

template <typename T>
T& Vec<T>::at(const int pos)
{
	if (!(pos >= 0 && pos < this->sz)) throw std::out_of_range("Vector out of range error");
	return this->elem[pos];
}

template <typename T>
void Vec<T>::set(const unsigned int pos, const T obj)
{
	if (!(this->sz + 1 < this->_space)) this->reserve(sz * this->_DEF_EXT_VAL);

	if (!(pos >= 0 && pos < this->sz)) throw std::out_of_range("Vector out of range error");
	this->elem[pos] = obj;
}

template <typename T>
T Vec<T>::get(const int pos)
{
	if (!(pos >= 0 && pos < this->sz)) throw std::out_of_range("Vector out of range error");

	return this->elem[pos];
}

template <typename T>
void Vec<T>::push_back(const T obj)
{
	if (!(this->sz + 1 < this->_space)) this->reserve(sz * this->_DEF_EXT_VAL);

	this->elem[sz] = obj;
	this->sz++;

}

template <typename T>
void Vec<T>::pop_back()
{
	T* new_array = new T[this->_space];
	std::copy(this->elem, this->elem + sz - 1, new_array);
	delete[] this->elem;
	this->elem = new_array;
	--this->sz;
}

template <typename T>
typename Vec<T>::iterator Vec<T>::reserve(unsigned int new_space)
{
	T* new_elem = new T[new_space];
	std::copy(elem, elem + sz, new_elem);
	delete[] elem;
	this->elem = new_elem;

	this->_space = new_space;

	return this->begin();
}


template <typename T>
Vec<T>::~Vec()
{
	delete[] elem;
}
