
// ex01 = serialization avec reinterpret_cast
#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include <stdint.h> // pour uintptr_t = un entier garanti assez grand pour contenir un pointeur
# include "Data.hpp"

class Serializer
{
private:
	// tout en private car le sujet dit que Serializer doit pas etre instanciable
	Serializer();
	Serializer(Serializer const &other);
	~Serializer();
	Serializer &operator=(Serializer const &other);

public:
	// 2 methodes statiques (pas d'objet), comme demande par le sujet
	static uintptr_t	serialize(Data *ptr);     // pointeur -> entier
	static Data			*deserialize(uintptr_t raw); // entier -> pointeur (l'inverse)
};

#endif
