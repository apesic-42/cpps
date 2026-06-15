#include <iostream>
#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	PmergeMe	thing;

	if (argc < 3) // le sujet veut au moins 2 nombres a trier (argv[0] = prog)
	{
		std::cout << "Not enough arguments!" << std::endl;
		return (1);
	}
	// validation : chaque argument doit etre uniquement des chiffres
	for (int i = 1; argv[i]; i++)
	{
		std::string	test;
		test = argv[i];
		// find_first_not_of renvoie npos si tout est valide. ca rejette aussi le
		// signe '-' donc les negatifs sont refuses (le sujet veut des positifs)
		if (test.find_first_not_of("0123456789") != std::string::npos)
		{
			std::cout << "Error" << std::endl;
			return (1);
		}
	}
	std::cout << "Before:"; // on affiche la sequence non triee
	for (int i = 1; argv[i]; i++)
		std::cout << " " << argv[i];
	std::cout << std::endl;
	thing.load_dq(argv);   // tri + chrono sur le deque
	thing.load_vctr(argv); // tri + chrono sur le vector (pour comparer)
}
