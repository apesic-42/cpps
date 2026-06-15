
#include "C.hpp"

// classe vide, forme canonique identique a A et B
C::C(void) {}

C::C(const C& other) { *this = other; }

C::~C(void) {}

C&	C::operator=(const C&) { return (*this); }

