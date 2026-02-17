

#include <iostream>
#include <string>
#include "Animal.hpp"

Animal::Animal(void): type("Animal")
{
	std::cout << " -> default Animal constructor called." << std::endl;
}

Animal::Animal(std::string type): type(type)
{
	std::cout << " -> parametric Animal constructor called." << std::endl;
}

Animal::Animal(const Animal &src)
{
	std::cout << " -> copy Animal constructor called." << std::endl;
	*this = src;
}

Animal::~Animal(void)
{
	std::cout << " -> Animal destructor called." << std::endl;
}

Animal	&Animal::operator =(const Animal &src)
{
	if (this != &src)
	{
		std::cout << " -> copy assignment Animal called." << std::endl;
		this->type = src.type;
	}
	return *this;
}

std::string	Animal::getType(void) const
{
	return this->type;
}

void	Animal::makeSound(void) const
{
	std::cout << "As an animal, honeslty I don't really have a sound..." << std::endl;
}
