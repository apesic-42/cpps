
#include <iostream>
#include <string>
#include "WrongCat.hpp"

WrongCat::WrongCat(void): WrongAnimal("WrongCat")
{
	std::cout << " -> default WrongCat constructor called." << std::endl;
}

WrongCat::WrongCat(const WrongCat &src): WrongAnimal(src.type)
{
	std::cout << " -> copy WrongCat constructor called." << std::endl;
	*this = src;
}

WrongCat::~WrongCat(void)
{
	std::cout << " -> WrongCat destructor called." << std::endl;
}

WrongCat	&WrongCat::operator =(const WrongCat &src)
{
	if (this != &src)
	{
		std::cout << " -> copy assignment WrongCat called." << std::endl;
		this->type = src.type;
	}
	return *this;
}

void	WrongCat::makeSound(void) const
{
	std::cout << "Meow !" << std::endl;
}
