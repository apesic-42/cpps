
// main de test pour Span : on couvre le cas du sujet + les cas d'erreur + la deep copy + un gros test

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Span.hpp"

int main(int, char**)
{
	// cas exact du sujet : {6,3,17,9,11} doit donner shortest=2 (entre 9 et 11) et longest=14 (entre 3 et 17)
	std::cout << "Test subject main, should output (2, 14): ";
	Span sp = Span(5);
	int	array[] = {6, 3, 17, 9, 11};
	// on remplit avec une plage d'iterateurs (ici des pointeurs sur le tableau C)
	sp.insertMany(array, array + sizeof(array)/sizeof(array[0])); // calcul du nb d'elements du tableau
	std::cout << "(" << sp.shortestSpan() << ", " << sp.longestSpan() << ")" << std::endl;

	Span	empty = Span(); // span de taille 0, sert a tester les exceptions

	// test 1 : ajouter dans un span plein (taille 0) doit throw
	std::cout << "Trying to add number to a 0 sized span : ";
	try
	{
		empty.addNumber(42);
		std::cout << "No problem ?" << std::endl;
	}
	catch (std::exception &e) // on catch tous ce qui herrite de std::exception
	{
		std::cout << e.what() << std::endl; // what() nous donne le message de l'exception
	}
	std::cout << std::endl;

	// test 2 : longestSpan sur span vide doit throw aussi
	std::cout << "Trying to find maximum of a 0 sized span : ";
	try
	{
		empty.longestSpan();
		std::cout << "No problem ?" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;

	// test 3 : shortestSpan sur span vide doit throw
	std::cout << "Trying to find minimum of a 0 sized span : ";
	try
	{
		empty.shortestSpan();
		std::cout << "No problem ?" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;

	// test 4 : deep copy. on modifie la copie l2 et on verifie que l'original l1 change pas
	std::cout << "Testing deep copy : ";
	Span	l1 = Span(3);
	l1.addNumber(42);
	l1.addNumber(21);
	Span	l2 = l1; // copie
	l2.addNumber(13); // si la copie est superficiel, ca toucherait aussi l1
	if (l1.shortestSpan() == l2.shortestSpan())
		std::cout << "Bad deep copy !" << std::endl; // memes spans = la copie a affecte l'original = mauvais
	else
		std::cout << "OK" << std::endl;
	std::cout << std::endl;

	// test 5 : gros test, le sujet demande au moins 10000 elements, ici 1 million pour etre large
	size_t		crazy_size = 1000000;
	Span		crazy_span = Span(crazy_size);
	std::cout << "Fill a " << crazy_size << " sized span with random values." << std::endl;
	crazy_span.fillWithRandom(crazy_size);
	std::cout << "    ShortestSpan(): " << crazy_span.shortestSpan() << std::endl;
	std::cout << "    LongestSpan(): " << crazy_span.longestSpan() << std::endl;

	return 0;
}
