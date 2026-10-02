#include <iostream>
#include <string>
#include <climits> // INT_MAX : un argument doit tenir dans un int
#include <cstdlib> // strtol
#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	PmergeMe	thing;

	if (argc < 2) // il faut au moins 1 nombre (argv[0] = prog). 1 seul = deja trie, c'est valide
	{
		std::cerr << "Error" << std::endl; // le sujet veut les erreurs sur stderr
		return (1);
	}
	// validation : chaque argument doit etre un entier positif qui tient dans un int
	for (int i = 1; argv[i]; i++)
	{
		std::string	test(argv[i]);

		// find_first_not_of renvoie npos si tout est chiffre. ca rejette aussi le signe '-' donc les negatifs sont refuses (le sujet veut des positifs
		// empty : sinon "" passait pour 0. strtol en long (64 bits) : pas de debordement silencieux comme atoi, on compare a INT_MAX
		if (test.empty() || test.find_first_not_of("0123456789") != std::string::npos
			|| std::strtol(argv[i], NULL, 10) > INT_MAX)
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}
	}
	std::cout << "Before:"; // on affiche la sequence non triee
	for (int i = 1; argv[i]; i++)
		std::cout << " " << argv[i];
	std::cout << std::endl;
	thing.load_dq(argv);   // tri + chrono sur le deque
	thing.load_vctr(argv); // tri + chrono sur le vector (pour comparer
}
