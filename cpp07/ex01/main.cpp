// main.cpp ex01 : on teste iter avec plusieurs types de tableaux et plusieurs callbacks
#include <iostream>
#include <string>
#include "iter.hpp"

// print est lui meme un template : ca prouve qu'on peut passer un template instancie comme 3e param (demande du sujet)
template <typename T>
void print(T const &x) // const ref car print modifie rien, juste affiche
{
	std::cout << x << std::endl;
}

void increment(int &x) // fonction normale (pas template) qui modifie l'element : x& pour modifier l'original dans le tableau
{
	x++;
}

void toUpper(std::string &s) // callback specifique aux string : montre que iter marche avec des fonctions variees
{
	for (size_t i = 0; i < s.length(); i++)
		s[i] = std::toupper(s[i]); // met chaque caractere en majuscule
}

int main(void)
{
	std::cout << "=== Int array ===" << std::endl;
	int intArr[] = {1, 2, 3, 4, 5};
	::iter(intArr, 5, print<int>); // print<int> et pas print : on peut pas prendre l'adresse d'un template, faut l'instancier d'abord

	std::cout << "=== After increment ===" << std::endl;
	::iter(intArr, 5, increment); // ici iter modifie le tableau (increment prend un int&)
	::iter(intArr, 5, print<int>);

	std::cout << "=== String array ===" << std::endl;
	std::string strArr[] = {"hello", "world", "foo"};
	::iter(strArr, 3, print<std::string>); // meme iter mais T = std::string (deduit tout seul depuis strArr)

	std::cout << "=== After toUpper ===" << std::endl;
	::iter(strArr, 3, toUpper);
	::iter(strArr, 3, print<std::string>);

	std::cout << "=== Double array ===" << std::endl;
	double dArr[] = {1.1, 2.2, 3.3};
	::iter(dArr, 3, print<double>); // encore un autre type, T = double

	std::cout << "=== Const int array ===" << std::endl;
	const int constArr[] = {10, 20, 30}; // tableau const : c'est la surcharge const de iter qui est appelee ici
	::iter(constArr, 3, print<int>);

	return 0;
}
