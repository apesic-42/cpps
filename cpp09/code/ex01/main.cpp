#include <iostream>
#include <cstdlib> // std::isdigit vient de <cctype> mais souvent dispo via ces headers
#include "RPN.hpp"

int	main(int argc, char **argv)
{
	std::string	arg;  // copie de l'expression a evaluer
	RPN			calc; // notre calculatrice a base de stack
	std::string	obj;  // le token courant

	if (argc < 2) // il faut l'expression en argument
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	arg = argv[1];
	arg.push_back(' '); // espace sentinelle a la fin pour delimiter le dernier token
	while (arg[0] == ' ' || arg[0] == '\t') // skip les espaces du debut
		arg.erase(0, 1);
	while (arg.length())
	{
		// on prend le token : tout jusqu'au prochain espace ou tab
		obj = arg.substr(0, arg.find_first_of(" \t"));
		if (obj == "+" || obj == "-" || obj == "/" || obj == "*")
			calc.operation(obj[0]); // c'est un operateur
		// sinon ca doit etre UN seul chiffre (le sujet limite a < 10)
		else if (obj.length() != 1 || !std::isdigit(obj[0]))
		{
			std::cerr << "Error" << std::endl; // multi-chiffres / lettres = rejete
			return (1);
		}
		else
			calc.add_num(obj[0] - '0'); // char -> int via le code ascii (C++98)
		while (arg[0] && arg[0] != ' ' && arg[0] != '\t') // bouffe le token traite
			arg.erase(0, 1);
		while (arg[0] == ' ' || arg[0] == '\t') // bouffe les espaces suivants
			arg.erase(0, 1);
	}
	std::cout << calc.result() << std::endl; // affiche le resultat final
}
