#include <iostream>

template <typename FT, typename ST> // first type, second type
struct Pair
{
	FT first;
	ST second;

	Pair(const FT first_val, const ST second_val);
};

int main()
{
	Pair<int, float> some_pair(10, 0.2);
	std::cout << some_pair.first << " and " << some_pair.second;
	return 0;
}

template <typename FT, typename ST> 
Pair<FT, ST>::Pair(const FT first_val, const ST second_val)
	: first{ first_val }, second{ second_val }
{}
