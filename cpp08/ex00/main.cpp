
#include <iostream>
#include <list>
#include <vector>
#include <deque>

#include "easyfind.hpp"

int main(int, char**)
{
	std::cout << "=== Test with std::list ===" << std::endl;
	std::list<int>	l;
	l.push_back(42);
	l.push_back(21);
	l.push_back(1337);
	l.push_back(84);

	std::list<int>::iterator it = easyfind(l, 21);
	if (it == l.end())
		std::cout << "Can't find this element..." << std::endl;
	else
		std::cout << "Element " << *it << " found !" << std::endl;

	it = easyfind(l, 999);
	if (it == l.end())
		std::cout << "Element 999 not found (expected)." << std::endl;
	else
		std::cout << "Element " << *it << " found !" << std::endl;

	std::cout << std::endl << "=== Test with std::vector ===" << std::endl;
	std::vector<int>	v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	std::vector<int>::iterator vit = easyfind(v, 30);
	if (vit == v.end())
		std::cout << "Can't find this element..." << std::endl;
	else
		std::cout << "Element " << *vit << " found !" << std::endl;

	vit = easyfind(v, 42);
	if (vit == v.end())
		std::cout << "Element 42 not found (expected)." << std::endl;
	else
		std::cout << "Element " << *vit << " found !" << std::endl;

	std::cout << std::endl << "=== Test with std::deque ===" << std::endl;
	std::deque<int>	d;
	d.push_back(5);
	d.push_back(10);
	d.push_back(15);

	std::deque<int>::iterator dit = easyfind(d, 5);
	if (dit == d.end())
		std::cout << "Can't find this element..." << std::endl;
	else
		std::cout << "Element " << *dit << " found !" << std::endl;

	dit = easyfind(d, 100);
	if (dit == d.end())
		std::cout << "Element 100 not found (expected)." << std::endl;
	else
		std::cout << "Element " << *dit << " found !" << std::endl;

	return 0;
}
