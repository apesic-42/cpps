
// main de test pour easyfind : on teste avec 3 containers differents pour prouver
// que le template est generique (le sujet demande "a container of integers")
#include <iostream>
#include <list>   // std::list = liste doublement chainee
#include <vector> // std::vector = tableau dynamique
#include <deque>  // std::deque = double ended queue

#include "easyfind.hpp"

int main(int, char**)
{
	std::cout << "=== Test with std::list ===" << std::endl;
	std::list<int>	l;
	l.push_back(42);
	l.push_back(21);
	l.push_back(1337);
	l.push_back(84);

	// on stock le retour dans un iterator du meme type que le container
	std::list<int>::iterator it = easyfind(l, 21);
	if (it == l.end()) // si == end() c'est que l'element existe pas (convention STL)
		std::cout << "Can't find this element..." << std::endl;
	else
		std::cout << "Element " << *it << " found !" << std::endl; // *it pour dereferencer et avoir la valeur

	it = easyfind(l, 999); // cas ou l'element est pas la, doit tomber sur end()
	if (it == l.end())
		std::cout << "Element 999 not found (expected)." << std::endl;
	else
		std::cout << "Element " << *it << " found !" << std::endl;

	// meme code mais avec un vector : le template s'adapte tout seul
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

	// et encore avec un deque, pareille ca marche sans rien changer au template
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
