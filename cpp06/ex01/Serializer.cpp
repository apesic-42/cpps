
#include "Serializer.hpp"

// forme canonique definie mais en private => inutilisable (classe pas instanciable)
// (void)other = on ignore le param pour eviter le warning -Wunused
Serializer::Serializer() {}
Serializer::Serializer(Serializer const &other) { (void)other; }
Serializer::~Serializer() {}
Serializer &Serializer::operator=(Serializer const &other) { (void)other; return (*this); }

// serialize : prend les bits bruts du pointeur et les presente comme un entier
// reinterpret_cast car on bidouille direct un pointeur en entier (types non lies)
// static_cast refuserait de compiler ici, et le cast C serait justement ce qu'on evite
uintptr_t Serializer::serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

// deserialize : meme operation dans l'autre sens, on retombe sur le pointeur d'origine
// la norme garantit que l'aller-retour uintptr_t <-> pointeur redonne le meme pointeur
Data *Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}
