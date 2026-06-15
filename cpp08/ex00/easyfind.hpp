
// ex00 easyfind : function template qui doit marcher avec n'importe quel container
// comme demander par le sujet (list, vector, deque...) car on connait pas le type a l'avance
#ifndef EASYFIND_H
# define EASYFIND_H

# include <algorithm> // pour std::find (algorithme STL)

template<typename T> // template car on connait pas le type du container, juste qu'il contient des int
typename T::iterator	easyfind(T &elems, int el) // typename obligatoire : T::iterator est un type dependant du template
{
	// std::find de <algorithm> parcour la plage [begin, end) et retourne un iterator sur le premier el trouve
	// si rien trouve il retourne end(), comme font les containers standards (idee prise du sujet)
	return std::find(elems.begin(), elems.end(), el);
}

#endif
