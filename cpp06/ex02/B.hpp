
#pragma once

#include "Base.hpp"

// B = pareil que A, juste un autre type concret a identifier (heritage public obligatoire)
class B : public Base {
	public:
		B(void);
		B(const B& other);
		~B(void);

		B&      operator=(const B&);
};

