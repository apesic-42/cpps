
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <cstdlib> // rand / srand
#include <ctime>   // time pour seeder le random

// generate : retourne un A, B ou C au hasard mais type en Base*
// du point de vue de l'appelant on sait pas le vrai type => c'est le probleme a resoudre
Base	*generate(void)
{
	int	random;

	random = rand() % 3; // tire 0, 1 ou 2
	if (random == 0)
		return (new A);
	if (random == 1)
		return (new B);
	if (random == 2)
		return (new C);
	else
		return (NULL); // inatteignable mais evite un warning
}

// version POINTEUR : dynamic_cast retourne NULL si le type reel correspond pas
void	identify(Base *p)
{
	// le if(pointeur) exploite la conversion pointeur -> bool (NULL = faux)
	if (dynamic_cast<A* >(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B* >(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C* >(p))
		std::cout << "C" << std::endl;
}

// version REFERENCE : interdit d'utiliser un pointeur dans le corps (sujet)
// une reference peut pas etre nulle => dynamic_cast jette std::bad_cast si ca rate
void	identify(Base &p)
{
	try
	{
		(void)dynamic_cast<A&>(p); // (void) car on veut juste savoir si ca passe
		std::cout << "A" << std::endl;
		return ; // important : on sort sinon on tenterait les autres casts pour rien
	}
	catch(std::exception& e) {} // on attrape l'echec en silence et on essaie le suivant
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

	srand(time(NULL)); // seed pour avoir des tirages differents a chaque run
	std::cout << "Identifying with pointers\n" << std::endl;

	// 5 tests avec la surcharge POINTEUR (identify(Base*))
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

	// 5 tests avec la surcharge REFERENCE : *base dereference, choisit identify(Base&)
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
