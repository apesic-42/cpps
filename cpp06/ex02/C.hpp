
#pragma once

#include "Base.hpp"

// C = troisieme type concret, meme principe que A et B (heritage public)
class C : public Base {
	public:
		C(void);
		C(const C& other);
		~C(void);

		C&      operator=(const C&);
};

