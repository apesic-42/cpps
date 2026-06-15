// main.cpp ex00 : c'est le main impose par le sujet, teste swap/min/max avec int et string
#include <iostream>
#include <string>
#include "whatever.hpp" // nos templates sont la dedans

int main(void)
{
	int a = 2;
	int b = 3;

	::swap(a, b); // :: force le namespace global pour pas confondre avec std::swap (sinon ambiguite)
	std::cout << "a = " << a << ", b = " << b << std::endl; // apres swap : a=3, b=2
	std::cout << "min( a, b ) = " << ::min(a, b) << std::endl; // le compilateur deduit T = int tout seul
	std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d); // meme template mais cette fois T = std::string (instanciation pour un autre type)
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min(c, d) << std::endl; // comparaison lexicographique (ordre alphabetique) pour les string
	std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;

	return 0;
}
