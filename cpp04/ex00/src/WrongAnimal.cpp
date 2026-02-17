
#include <iostream>
#include <string>
#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void): type("WrongAnimal")
{
	std::cout << " -> default WrongAnimal constructor called." << std::endl;
}

WrongAnimal::WrongAnimal(std::string type): type(type)
{
	std::cout << " -> parametric WrongAnimal constructor called." << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &src)
{
	std::cout << " -> copy WrongAnimal constructor called." << std::endl;
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
		std::cout << " -> copy assignment WrongAnimal called." << std::endl;
		this->type = src.type;
	}
	return *this;
}

std::string	WrongAnimal::getType(void) const
{
	return this->type;
}

void	WrongAnimal::makeSound(void) const
{
	std::cout << "As a wrong animal, I don't really have a sound..." << std::endl;
}
