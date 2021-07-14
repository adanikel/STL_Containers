#include <iostream>

template <typename FT, typename ST> // first type, second type
struct Pair
{
	FT first;
	ST second;

	Pair(const FT first_val, const ST second_val);
	Pair(const Pair<FT, ST>& pair_obj); // copy constructor
	Pair(Pair<FT, ST>&& pair_obj); // move constructor

	Pair<FT, ST>& operator=(const Pair<FT, ST>& pair_obj); // copy assignment
	Pair<FT, ST>& operator=(Pair<FT, ST>&& pair_obj); // move assignment

	void swap(Pair<FT, ST>& pair_obj);
};


int main()
{

	return 0;
}

template <typename FT, typename ST>
Pair<FT, ST>::Pair(const FT first_val, const ST second_val)
	: first{ first_val }, second{ second_val }
{}

template <typename FT, typename ST>
Pair<FT, ST>::Pair(const Pair<FT, ST>& pair_obj)
	: first{ pair_obj.first }, second{ pair_obj.second }
{}

template <typename FT, typename ST>
Pair<FT, ST>::Pair(Pair<FT, ST>&& pair_obj)
	: first{ std::move(pair_obj.first) }, second{ std::move(pair_obj.second) }
{}

template <typename FT, typename ST>
Pair<FT, ST>& Pair<FT, ST>::operator=(const Pair<FT, ST>& pair_obj)
{
	this->first = pair_obj.first;
	this->second = pair_obj.second;

	return *this;
}

template <typename FT, typename ST>
Pair<FT, ST>& Pair<FT, ST>::operator=(Pair<FT, ST>&& pair_obj)
{
	this->first = std::move(pair_obj.first);
	this->second = std::move(pair_obj.second);

	return *this;
}

template <typename FT, typename ST>
void Pair<FT, ST>::swap(Pair<FT, ST>& pair_obj)
{
	std::swap(this->first, pair_obj.first);
	std::swap(this->second, pair_obj.second);
}

