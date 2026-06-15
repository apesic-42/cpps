
#pragma once

#include "Base.hpp"

// A herite PUBLIQUEMENT de Base (le sujet l'impose)
// sans heritage public, dynamic_cast<A*>(base) pourrait pas retrouver le A
class A : public Base {
	public:
		// classe vide (aucune donnee) mais on garde la forme canonique par habitude
		A(void);
		A(const A& other);
		~A(void);

		A&	operator=(const A&); // pas le nom (le nom est fixe, on retourne *this)
};

