// main.cpp ex02 : on teste tous les cas demandes par le sujet (vide, taille, deep copy, hors limites, autre type)
#include <iostream>
#include <string>
#include "Array.hpp"

int main(void)
{
	std::cout << "=== Empty array ===" << std::endl;
	Array<int> empty; // construction sans parametre = tableau vide
	std::cout << "Size: " << empty.size() << std::endl; // doit afficher 0

	std::cout << "\n=== Int array of 5 ===" << std::endl;
	Array<int> intArr(5); // construction avec n : 5 elements (Array<int> = instanciation du template avec T=int)
	for (unsigned int i = 0; i < intArr.size(); i++)
	{
		intArr[i] = i * 10; // operator[] non-const utilise ici pour ecrire
		std::cout << "intArr[" << i << "] = " << intArr[i] << std::endl;
	}

	std::cout << "\n=== Copy constructor (deep copy) ===" << std::endl;
	Array<int> copy(intArr); // appelle le constructeur de copie
	copy[0] = 999; // on modifie la copie
	std::cout << "copy[0] = " << copy[0] << std::endl;
	std::cout << "intArr[0] = " << intArr[0] << " (unchanged)" << std::endl; // l'original bouge pas : preuve de la deep copy

	std::cout << "\n=== Assignment operator (deep copy) ===" << std::endl;
	Array<int> assigned; // d'abord vide
	assigned = intArr; // puis on assigne : appelle operator=
	assigned[1] = 888; // on modifie la copie
	std::cout << "assigned[1] = " << assigned[1] << std::endl;
	std::cout << "intArr[1] = " << intArr[1] << " (unchanged)" << std::endl; // original intact, deep copy ok

	std::cout << "\n=== Out of bounds ===" << std::endl;
	try
	{
		intArr[42] = 0; // index 42 hors limites : operator[] doit jeter une exception
	}
	catch (std::exception &e) // on catch tous ce qui herrite de std::exception (out_of_range en fait partie)
	{
		std::cout << "Exception: " << e.what() << std::endl; // what() = message de l'exception
	}

	std::cout << "\n=== String array ===" << std::endl;
	Array<std::string> strArr(3); // meme classe template mais T = std::string : prouve que c'est generique
	strArr[0] = "Hello";
	strArr[1] = "myfriend";
	strArr[2] = "42";
	for (unsigned int i = 0; i < strArr.size(); i++)
		std::cout << "strArr[" << i << "] = " << strArr[i] << std::endl;

	std::cout << "\n=== Default init (int should be 0) ===" << std::endl;
	Array<int> zeros(3); // grace aux () dans new T[n](), les int sont initialises a 0 et pas a du garbage
	for (unsigned int i = 0; i < zeros.size(); i++)
		std::cout << "zeros[" << i << "] = " << zeros[i] << std::endl;

	return 0;
}
