
#include <iostream>
#include <string>
#include "WrongCat.hpp"

WrongCat::WrongCat(void): WrongAnimal("WrongCat")
{
	std::cout << " -> Default WrongCat constructor called." << std::endl;
}

//WrongCat::WrongCat(std::string type): Animal(type)
//{
//	std::cout << " -> Parametric WrongCat constructor called." << std::endl;
//}

WrongCat::WrongCat(const WrongCat &src): WrongAnimal(src._type)
{
	std::cout << " -> Copy WrongCat constructor called." << std::endl;
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
		std::cout << " -> Copy assignment WrongCat called." << std::endl;
		this->_type = src._type;
	}
	return *this;
}

void	WrongCat::makeSound(void) const
{
	std::cout << "Imma dominate the world, meow !" << std::endl;
}
