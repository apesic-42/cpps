#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void print(T const &x)
{
	std::cout << x << std::endl;
}

void increment(int &x)
{
	x++;
}

void toUpper(std::string &s)
{
	for (size_t i = 0; i < s.length(); i++)
		s[i] = std::toupper(s[i]);
}

int main(void)
{
	std::cout << "=== Int array ===" << std::endl;
	int intArr[] = {1, 2, 3, 4, 5};
	::iter(intArr, 5, print<int>);

	std::cout << "=== After increment ===" << std::endl;
	::iter(intArr, 5, increment);
	::iter(intArr, 5, print<int>);

	std::cout << "=== String array ===" << std::endl;
	std::string strArr[] = {"hello", "world", "foo"};
	::iter(strArr, 3, print<std::string>);

	std::cout << "=== After toUpper ===" << std::endl;
	::iter(strArr, 3, toUpper);
	::iter(strArr, 3, print<std::string>);

	std::cout << "=== Double array ===" << std::endl;
	double dArr[] = {1.1, 2.2, 3.3};
	::iter(dArr, 3, print<double>);

	return 0;
}
