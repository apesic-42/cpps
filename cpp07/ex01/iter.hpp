// iter.hpp : le function template iter du sujet (adresse tableau + longueur + fonction)
// comme c'est un template, tout est dans le header (instancie a la compilation, pas de .cpp)
#ifndef ITER_HPP // include guard contre la double inclusion (regle du sujet)
#define ITER_HPP

#include <cstddef> // pour size_t

// deux parametres de template : T = type des elements, F = type de la fonction callback
// F au lieu de void(*)(T&) parce que ca accepte aussi les templates instancies et les foncteurs (plus flexible)
template <typename T, typename F>
void iter(T *array, const size_t length, F func) // T* = adresse du tableau, length const car le sujet le demande (on la modifie pas)
{
	for (size_t i = 0; i < length; i++) // on parcours tout le tableau
		func(array[i]); // on appelle la fonction sur chaque element
}

// deuxieme surcharge pour les tableaux const : le sujet dit que ca doit marcher avec n'importe quel type de tableau
// sans ce overload const, passer un const int arr[] compilerait pas (le callback prendrait alors un T const &)
template <typename T, typename F>
void iter(const T *array, const size_t length, F func) // ici const T* pour accepter un tableau constant
{
	for (size_t i = 0; i < length; i++)
		func(array[i]);
}

#endif
