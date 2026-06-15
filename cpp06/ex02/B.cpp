
#include "B.hpp"

// classe vide, forme canonique identique a A
B::B(void) {}

B::B(const B& other) { *this = other; }

B::~B(void) {}

B&	B::operator=(const B&) { return (*this); }

