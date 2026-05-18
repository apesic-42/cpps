
#pragma once

#include "Base.hpp"

class C : public Base {
	public:
		C(void);
		C(const C& other);
		~C(void);

		C&      operator=(const C&);
};

