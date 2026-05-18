
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

Base	*generate(void)
{
	int	random;

	random = rand() % 3;
	if (random == 0)
		return (new A);
	if (random == 1)
		return (new B);
	if (random == 2)
		return (new C);
	else
		return (NULL);
}

void	identify(Base *p)
{
	if (dynamic_cast<A* >(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B* >(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C* >(p))
		std::cout << "C" << std::endl;
}

void	identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return ;
	}
	catch(std::exception& e) {}
	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return ;
	}
	catch(std::exception& e) {}
	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return ;
	}
	catch(std::exception& e) {}
}


int	main()
{
	Base	*base;

	srand(time(NULL));
	std::cout << "Identifying with pointers\n" << std::endl;

	base = generate();
	identify(base);
	delete base;

	base = generate();
	identify(base);
	delete base;

	base = generate();
	identify(base);
	delete base;

	base = generate();
	identify(base);
	delete base;
	
	base = generate();
	identify(base);
	delete base;

	std::cout << "\nIdentifying with references\n" << std::endl;

	base = generate();
	identify(*base);
	delete base;

	base = generate();
	identify(*base);
	delete base;

	base = generate();
	identify(*base);
	delete base;

	base = generate();
	identify(*base);
	delete base;

	base = generate();
	identify(*base);
	delete base;
}
