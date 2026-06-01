#include <iostream>
#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	PmergeMe	thing;

	if (argc < 3)
	{
		std::cout << "Not enough arguments!" << std::endl;
		return (1);
	}
	for (int i = 1; argv[i]; i++)
	{
		std::string	test;
		test = argv[i];
		if (test.find_first_not_of("0123456789") != std::string::npos)
		{
			std::cout << "Error" << std::endl;
			return (1);
		}
	}
	std::cout << "Before:";
	for (int i = 1; argv[i]; i++)
		std::cout << " " << argv[i];
	std::cout << std::endl;
	thing.load_dq(argv);
	thing.load_vctr(argv);
}
