// whatever.hpp : ici on met les 3 function templates du sujet (swap, min, max)
// le sujet impose que les templates soient definis dans le header, pas de .cpp
#ifndef WHATEVER_HPP // include guard pour eviter la double inclusion (demande par les regles)
#define WHATEVER_HPP

template <typename T> // template <typename T> = T sera remplace par le vrai type a l'appel (int, string...)
void swap(T &a, T &b) // T& (reference) pour modifier directement les variables de l'appelant, pas des copies
{
	T tmp = a; // on sauvegarde a dans tmp avant de l'ecraser
	a = b; // a prend la valeur de b
	b = tmp; // b prend l'ancienne valeur de a (algo classique du swap en 3 etapes)
}

template <typename T> // generique : marche avec tout type qui supporte l'operateur <
T const &min(T const &a, T const &b) // const ref en parametre (pas de copie, on modifie pas) et en retour (on renvoie une ref vers a ou b)
{
	if (a < b) // a < b (pas <=) : si a == b la condition est fausse donc on renvoie b
        return a;
    else
        return b; // si egaux on renvoie le second, exactement ce que demande le sujet
}

template <typename T> // meme principe que min mais avec >
T const &max(T const &a, T const &b)
{
    if (a > b) // a > b (pas >=) pour que en cas d'egalite on retourne b (le second)
           return a;
       else
           return b;
}

#endif
