
#pragma once

#include "Base.hpp"

class A : public Base {
	public:
		A(void);
		A(const A& other);
		~A(void);

		A&	operator=(const A&);
};

