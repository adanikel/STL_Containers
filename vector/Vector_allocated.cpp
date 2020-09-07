#include <iostream>

template <typename T>
class Vec
{
private:
	unsigned int space;

public:
	unsigned int sz; // size of array
	T* elem{ nullptr }; // will be the array, initialized as null pointer

	Vec(unsigned int inp1);
	Vec(std::initializer_list<T> lst);
	Vec(Vec& src_vec);
	Vec(Vec&& rvalue_vec) noexcept;

	Vec<T>& operator= (Vec<T>& obj); // redefining = operator
	Vec<T>& operator= (Vec<T>&& obj) noexcept; // redefining = operator for rvalue
	T& operator[] (const int index); // redefining [] operator
	T operator[] (const int index) const; // redefining [] operator for constant!! does not return a reference!!

	using iterator = T*;
	iterator begin() { return &(elem[0]); } // pointer to first element
	iterator end() { return &elem[sz - 1]; } // pointer to last element
	iterator insert(iterator plc, const T& obj); // insert new objects
	iterator erase(iterator plc); // erase existing objects

	void set(int pos, T obj);
	T get(int pos);
	void push_back(T obj);
	unsigned int getsize() const { return sz; };
	unsigned int get_elemsize() const { return sizeof(T); };
	void resize(unsigned int new_sz);
	inline bool empty() { return (sz == 0); };
	iterator reserve(unsigned int new_space);
	inline unsigned int capacity() { return space; };
	T& at(const int pos); // checks for out of range error unlike [] operators

	~Vec(); // destructor is a must since we are initializing an array on the heap
};


Vec<int> int_vec(int inp) // to test move constructor
{
	Vec<int> temp(inp);
	std::cout << std::endl << "initialized vector! elem location:" << temp.elem;

	return temp;
}


int main()
{
	Vec<int> var(3);
	var.set(0, 0);

	var.resize(9);
	var[1] = 1;
	var[2] = 2;
	var[3] = 3;
	var[4] = 4;
	var[5] = 5;
	var[6] = 6;
	var[7] = 7;
	var[8] = 8;


	Vec<int>::iterator itr;
	itr = var.begin();
	std::cout << "will insert soon" << std::endl;
	std::cout << "old size is " << var.getsize() << std::endl;

	for (unsigned int idx = 0; idx != var.sz; idx++)
	{
		std::cout << var[idx] << std::endl;
	};
	var.insert(itr + 1, 0123);
	std::cout << "inserted!!" << std::endl;
	for (unsigned int idx = 0; idx != var.sz; idx++)
	{
		std::cout << var[idx] << std::endl;
	};
	std::cout << "new size is " << var.getsize() << std::endl;

	return 0;
}



template <typename T>
Vec<T>::Vec(const unsigned int inp1)
	:sz{ inp1 }, space{ inp1 * 2 }, elem{ new T[space] }
{}

template <typename T>
Vec<T>::Vec(std::initializer_list<T> lst) // initialize as a list
	: sz{ lst.size() }, space{ lst.size() * 2 }, elem{ new T[space] }
{
	T* idx_ptr = elem;
	for (int idx = 0; idx != sz; idx++) // pass initializer list elements to vector
	{
		this->elem[idx] = *(lst.begin() + idx);
	}
}

template <typename T>
Vec<T>::Vec(Vec& src_vec) // initialize using another vector - copy it
	:sz{ src_vec.sz }, space{ src_vec.space }, elem{ new T[space] }
{
	std::cout << std::endl << "A copy constructor was called!" << std::endl;
	std::copy(src_vec.elem, src_vec.elem + sz, this->elem);

}

template <typename T>
Vec<T>::Vec(Vec<T>&& rvalue_vec) noexcept
	:sz{ rvalue_vec.sz }, space{ rvalue_vec.space }
{
	std::cout << std::endl << "An rvalue constructor was called!" << std::endl;
	this->elem = rvalue_vec.elem; // snatch pointer
	rvalue_vec.elem = nullptr; // nullify rvalue elem pointer
	std::cout << std::endl << "The address of 'elem' in the recently initialized vec is " << this->elem;

}

template <typename T>
typename Vec<T>::iterator Vec<T>::erase(Vec<T>::iterator plc)
{
	for (iterator temp = plc; temp != this->end(); temp++)
	{
		*temp = *(temp + 1);
		std::cout << *temp << std::endl;
	};

	this->elem[sz - 1] = 0; // sort of destroy? allc is better here
	--this->sz;

	return plc;
}

template <typename T>
typename Vec<T>::iterator Vec<T>::insert(Vec<T>::iterator plc, const T& obj)
{
	unsigned int loc = plc - this->begin(); // might be invalidated if 'reserve' is called, and therefore I save the location
	if (!(this->sz + 1 < this->space)) this->reserve(sz * 2);
	plc = this->begin() + loc;

	for (iterator temp = this->end() + 1; temp != plc; temp--) // end()+1 works because we have that space reserved!
	{
		*temp = *(temp - 1);
	};

	*plc = obj;

	++this->sz;

	return plc;
}


template <typename T>
Vec<T>& Vec<T>::operator= (Vec<T>& obj) // copy
{
	std::cout << std::endl << "'=' operator was called!" << std::endl;
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
	std::cout << std::endl << "rvalue '=' operator was called!" << std::endl;
	delete[] this->elem; // reallocate current memory
	this->sz = obj.sz;
	this->space = obj.space;

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
void Vec<T>::set(const int pos, const T obj)
{
	if (!(this->sz + 1 < this->space)) this->reserve(sz * 2);

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
	if (!(this->sz + 1 < this->space)) this->reserve(sz * 2);

	this->elem[sz] = obj;
	this->sz++;

}

template <typename T>
void Vec<T>::resize(unsigned int new_sz)
{
	unsigned int diff = this->sz - new_sz;

	if (new_sz <= this->sz) // delete excess
	{

		for (unsigned int idx = new_sz; idx != this->sz; idx++)
		{
			this->elem[idx] = 0;

		}

	}
	else if (new_sz > this->sz) // push_back new ones and update size
	{
		for (unsigned int idx = this->sz; idx != new_sz; idx++)
		{
			this->push_back(0);
		}
	}
	this->sz = new_sz;

}

template <typename T>
typename Vec<T>::iterator Vec<T>::reserve(unsigned int new_space)
{
	T* temp = new T[new_space];
	std::copy(elem, elem + sz, temp);
	delete[] elem;
	this->elem = new T[new_space];
	std::copy(temp, temp + sz, elem);

	delete[] temp;
	this->space = new_space;

	return this->begin();
}


template <typename T>
Vec<T>::~Vec()
{
	std::cout << std::endl << "Destructor was called";
	delete[] elem;
}