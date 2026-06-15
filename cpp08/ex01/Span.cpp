
// implementation de la classe Span
#include <numeric>		// pour std::adjacent_difference (calcule les diff entre elements voisins)
#include <iostream>
#include <stdlib.h>		// pour rand() et srand()
#include <time.h>		// pour time() qui sert de seed au random
#include "Span.hpp"

// constructeur par defaut : max_size a 0, donc on peut rien ajouter dedans
Span::Span(void)
	: _max_size(0) // init dans la liste d'init car _max_size est const
{

}

// constructeur principal du sujet : on fixe la taille max
Span::Span(const unsigned int max_size)
	: _max_size(max_size)
{

}

// constructeur de copie : on init _max_size (obligatoire car const) puis on delegue a operator=
Span::Span(const Span &src)
	: _max_size(src._max_size)
{
	*this = src;
}

Span::~Span(void)
{
	// rien a faire, le vector se detruit tout seul (RAII)
}

Span	&Span::operator =(const Span &src)
{
	if (this != &src) // protection contre l'auto affectation
		this->_elems = src._elems; // on copie que _elems, pas _max_size car il est const
	return *this;
}

void	Span::addNumber(const int num)
{
	// on verifie qu'on a pas atteint la limite du sujet ni la limite physique du vector
	if (this->_elems.size() >= this->_max_size ||
		this->_elems.size() >= this->_elems.max_size())
		throw Span::MaxSizeReachedException(); // throw si plein, comme demande par le sujet
	this->_elems.push_back(num); // sinon on ajoute en fin du vector
}

// shortestSpan : trouve le plus petit ecart entre 2 nombres stockes
int	Span::shortestSpan(void) const
{
	if (this->_elems.size() <= 1) // 0 ou 1 element = pas d'ecart possible
		throw Span::EmptySpanException();

	std::vector<int> temp = this->_elems; // copie car la methode est const, on doit pas modifier l'original
	std::sort(temp.begin(), temp.end()); // std::sort de <algorithm>, apres tri les valeurs proches sont voisines
	// adjacent_difference (de <numeric>) ecrit dans temp les diff entre chaque paire d'elements consecutifs
	std::adjacent_difference(temp.begin(), temp.end(), temp.begin());

	// begin()+1 important : temp[0] garde la 1ere valeur brute (convention de adjacent_difference)
	// donc on cherche le min seulement sur les vraies differences
	return *std::min_element(temp.begin() + 1, temp.end()); // *  pour dereferencer l'iterateur retourne
}

// longestSpan : plus simple, le plus grand ecart c'est toujours max - min
int	Span::longestSpan(void) const
{
	if (this->_elems.size() <= 1)
		throw Span::EmptySpanException();

	// max_element et min_element parcourent le container en O(n) et retournent un iterateur
	int	max = *std::max_element(this->_elems.begin(), this->_elems.end());
	int	min = *std::min_element(this->_elems.begin(), this->_elems.end());

	return max - min; // pas besoin de trier ici
}

// utilitaire : remplit le span avec des valeurs aleatoires pour les gros tests
void	Span::fillWithRandom(size_t num)
{
	srand(time(NULL)); // seed du random avec l'heure courante
	for (size_t cur = 0; cur < num; cur++)
		this->addNumber(rand()); // on reutilise addNumber pour profiter du check de capacite
}


// les messages de chaque exception, retournes par what()
const char*	Span::MaxSizeReachedException::what(void) const throw()
{
	return "Maximum size for Span reached!";
}

const char*	Span::EmptySpanException::what(void) const throw()
{
	return "Span is empty!";
}
