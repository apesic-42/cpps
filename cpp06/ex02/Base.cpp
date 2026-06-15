
#include "Base.hpp"

// destructeur vide mais il DOIT exister (sinon erreur de link)
// c'est sa presence virtuelle qui genere la vtable necessaire au dynamic_cast
Base::~Base(void) {}
