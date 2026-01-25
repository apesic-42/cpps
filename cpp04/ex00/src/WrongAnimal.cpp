
#include <iostream>
#include <string>
#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void): _type("WrongAnimal")
{
	std::cout << " -> Default WrongAnimal constructor called." << std::endl;
}

WrongAnimal::WrongAnimal(std::string type): _type(type)
{
	std::cout << " -> Parametric WrongAnimal constructor called." << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &src)
{
	std::cout << " -> Copy WrongAnimal constructor called." << std::endl;
	*this = src;
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << " -> WrongAnimal destructor called." << std::endl;
}

WrongAnimal	&WrongAnimal::operator =(const WrongAnimal &src)
{
	if (this != &src)
	{
		std::cout << " -> Copy assignment WrongAnimal called." << std::endl;
		this->_type = src._type;
	}
	return *this;
}

std::string	WrongAnimal::getType(void) const
{
	return this->_type;
}

void	WrongAnimal::makeSound(void) const
{
	std::cout << "As a wrong animal, I don't really have a sound..." << std::endl;
}
