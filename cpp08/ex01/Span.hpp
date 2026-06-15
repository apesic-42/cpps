
// ex01 Span : classe qui stock au max N int et calcule le plus petit / plus grand ecart
// le sujet demande d'utiliser les containers et algorithmes de la STL au maximum
#ifndef SPAN_CLASS_H
# define SPAN_CLASS_H

# include <vector>		// std::vector = tableau dynamique, le container qu'on encapsule
# include <algorithm>	// pour std::sort, std::min_element, std::max_element (algos STL)

class Span {
private:
	const unsigned int	_max_size;	// taille max demande au constructeur, const car ca change jamais apres
	std::vector<int>	_elems;		// le vector gere sa memoire tout seul, pas de new/delete (RAII)

public:
	// orthodox canonical form, obligatoire du module 02 au 09
	Span(void);
	Span(const unsigned int max_size);	// le seul param du sujet : un unsigned int N
	Span(const Span &src);
	~Span(void);
	Span	&operator =(const Span &src);

	void	addNumber(const int num);	// ajoute un int, throw si deja plein (demande par le sujet)
	int		shortestSpan(void) const;	// plus petit ecart entre 2 nombres, throw si < 2 elements
	int		longestSpan(void) const;	// plus grand ecart, throw aussi si < 2 elements

	// insertMany : remplir le Span avec une plage d'iterateurs au lieu d'appeler addNumber 1000x
	// c'est le bonus demande par le sujet (eviter les milliers d'appels a addNumber)
	template<typename InputIt> // template car on connait pas le type de l'iterateur (pointeur, vector, list...)
	void	insertMany(InputIt begin, InputIt end)
	{
		while (begin != end) // on parcour la plage [begin, end) comme un algo STL
		{
			this->addNumber(*begin); // *begin pour avoir la valeur, on reutilise addNumber pour le check de capacite
			++begin;
		}
	}
	void	fillWithRandom(size_t num);	// utilitaire pour tester avec bcp d'elements (sujet demande >= 10000)

	// exceptions nestees dans Span, heritent de std::exception (pattern canonique C++98)
	class MaxSizeReachedException: public std::exception {
	public:
		virtual const char* what(void) const throw(); // throw() = cette fonction renvoie elle meme pas d'erreur
	};

	class EmptySpanException: public std::exception {
	public:
		virtual const char* what(void) const throw(); // what() surcharge pour retourner notre message
	};
};

#endif
