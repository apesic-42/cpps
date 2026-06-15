
// main minimal : tout le travail est dans la classe, on l'instancie jamais
#include <iostream>
#include "ScalarConverter.hpp"

int main(int argc, char const *argv[])
{
	// le sujet veut exactement un argument (le literal a convertir)
	if (argc != 2)
		std::cout << "convert: bad arguments!" << std::endl;
	else
		ScalarConverter::convert(argv[1]); // appel de la methode statique, sans objet
	return (0);
}
