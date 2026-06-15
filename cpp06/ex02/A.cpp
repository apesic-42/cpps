
#include "A.hpp"

// classe vide : rien a faire dans les fonctions, juste la forme canonique
A::A(void) {}

A::A(const A& other) { *this = other; } // copie qui delegue a l'operateur=

A::~A(void) {}

A&	A::operator=(const A&) { return (*this); } // aucun etat a copier, on rend juste *this
