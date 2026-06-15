
// main = demonstration : serialize puis deserialize doit redonner le meme pointeur
#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int	main()
{
	Data		*ptr;
	Data		*new_ptr;
	uintptr_t	raw; // la valeur entiere du pointeur

	ptr = new Data; // on cree un Data sur le tas
	ptr->data = "Fake Data!";

	raw = Serializer::serialize(ptr);       // pointeur -> entier
	new_ptr = Serializer::deserialize(raw); // entier -> pointeur

	// les deux pointent vers la MEME memoire, donc meme contenu
	std::cout << "Data of ptr: " << ptr->data << std::endl;
	std::cout << "Data of new_ptr: " << new_ptr->data << std::endl;

	// test : l'aller-retour doit redonner exactement le pointeur de depart
	if (ptr == new_ptr)
		std::cout << "Pointers are equal!" << std::endl;
	else
		std::cout << "Pointers are NOT equal!" << std::endl;

	delete ptr; // on delete que ptr : new_ptr est la meme zone (delete des 2 = double free)
}
