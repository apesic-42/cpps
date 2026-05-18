#include <iostream>
#include <string>
#include "Array.hpp"

int main(void)
{
	std::cout << "=== Empty array ===" << std::endl;
	Array<int> empty;
	std::cout << "Size: " << empty.size() << std::endl;

	std::cout << "\n=== Int array of 5 ===" << std::endl;
	Array<int> intArr(5);
	for (unsigned int i = 0; i < intArr.size(); i++)
	{
		intArr[i] = i * 10;
		std::cout << "intArr[" << i << "] = " << intArr[i] << std::endl;
	}

	std::cout << "\n=== Copy constructor (deep copy) ===" << std::endl;
	Array<int> copy(intArr);
	copy[0] = 999;
	std::cout << "copy[0] = " << copy[0] << std::endl;
	std::cout << "intArr[0] = " << intArr[0] << " (unchanged)" << std::endl;

	std::cout << "\n=== Assignment operator (deep copy) ===" << std::endl;
	Array<int> assigned;
	assigned = intArr;
	assigned[1] = 888;
	std::cout << "assigned[1] = " << assigned[1] << std::endl;
	std::cout << "intArr[1] = " << intArr[1] << " (unchanged)" << std::endl;

	std::cout << "\n=== Out of bounds ===" << std::endl;
	try
	{
		intArr[42] = 0;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\n=== String array ===" << std::endl;
	Array<std::string> strArr(3);
	strArr[0] = "Hello";
	strArr[1] = "World";
	strArr[2] = "42";
	for (unsigned int i = 0; i < strArr.size(); i++)
		std::cout << "strArr[" << i << "] = " << strArr[i] << std::endl;

	std::cout << "\n=== Default init (int should be 0) ===" << std::endl;
	Array<int> zeros(3);
	for (unsigned int i = 0; i < zeros.size(); i++)
		std::cout << "zeros[" << i << "] = " << zeros[i] << std::endl;

	return 0;
}
