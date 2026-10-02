#include <iostream>
#include <sstream> // istringstream : decoupe l'expression sur les espaces / tabs
#include <cctype>  // std::isdigit
#include "RPN.hpp"

//notation polonaise invers :
// On lit l'expression de gauche à droite :
// Nombre → on l'empile
// Opérateur → on dépile les 2 derniers, on calcule, on rempile le resultat


int	main(int argc, char **argv)
{
	RPN			calc; // notre calculatrice a base de stack
	std::string	obj;  // le token courant

	if (argc != 2) // il faut l'expression en argument, et une seule
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	std::istringstream	iss(argv[1]);
	while (iss >> obj) // >> saute tout seul les espaces et tabs, 1 token a la fois
	{
		if (obj == "+" || obj == "-" || obj == "/" || obj == "*")
			calc.operation(obj[0]); // c'est un operateur
		// sinon ca doit etre UN seul chiffre (le sujet limite a < 10)
		else if (obj.length() != 1 || !std::isdigit(obj[0]))
		{
			std::cerr << "Error" << std::endl; // multi-chiffres / lettres = rejete
			return (1);
		}
		else
			calc.add_num(obj[0] - '0');
	}
	std::cout << calc.result() << std::endl;
}
