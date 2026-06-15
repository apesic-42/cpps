// Array.hpp : la CLASS template du sujet (tableau generique avec new[], deep copy et bounds checking)
// classe template donc tout le corps est dans le header (le compilateur instancie a la compilation, pas de .cpp)
#ifndef ARRAY_HPP // include guard contre la double inclusion (regle du sujet)
#define ARRAY_HPP

#include <stdexcept> // pour std::out_of_range (herrite de std::exception, comme demande)

template <typename T> // T = type des elements, ca marche donc avec int, string, n'importe quoi
class Array
{
	private:
		T				*_array; // pointeur vers le tableau alloue dynamiquement avec new[]
		unsigned int	_size; // nombre d'elements (le sujet interdit l'allocation preventive donc pas de capacite en plus)

	public:
		Array(void) : _array(NULL), _size(0) {} // constructeur par defaut : tableau vide, _array a NULL

		Array(unsigned int n) : _array(new T[n]()), _size(n) {} // les () de new T[n]() = value-initialization, met les int a 0 (le tip du sujet)

		Array(Array const &src) : _array(NULL), _size(0) // constructeur de copie (forme canonique)
		{
			*this = src; // on delegue a l'operator= ; _array DOIT etre NULL avant car operator= fait delete[] en premier
		}

		~Array(void) // destructeur : libere la memoire pour eviter les fuites
		{
			delete[] _array; // delete[] sur NULL est safe par le standard, donc ok meme si tableau vide
		}

		Array &operator=(Array const &rhs) // operator= en deep copy (les deux tableaux restent independants)
		{
			if (this != &rhs) // protection contre l'auto-affectation (a = a), sinon on detruirait nos propres donnees
			{
				delete[] _array; // on libere l'ancien tableau
				_size = rhs._size;
				_array = new T[_size](); // nouveau tableau de la meme taille
				for (unsigned int i = 0; i < _size; i++)
					_array[i] = rhs._array[i]; // copie element par element (utilise l'operator= du type T)
			}
			return *this; // on retourne *this pour permettre le chainage a = b = c
		}

		T &operator[](unsigned int index) // version non-const : retourne une ref modifiable, permet arr[0] = 42
		{
			if (index >= _size) // unsigned int donc pas d'index negatif possible
				throw std::out_of_range("Array index out of bounds"); // exception si hors limites (demande du sujet)
			return _array[index];
		}

		T const &operator[](unsigned int index) const // version const : appelee quand l'Array est const, retour en lecture seule
		{
			if (index >= _size)
				throw std::out_of_range("Array index out of bounds");
			return _array[index];
		}

		unsigned int size(void) const // getter de la taille, const car ca modifie pas l'objet (le sujet l'exige)
		{
			return _size;
		}
};

#endif
