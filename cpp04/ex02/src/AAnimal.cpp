
#include <iostream>
#include <string>
#include "AAnimal.hpp"

AAnimal::AAnimal(void): _type("AAnimal")
{
	std::cout << " -> Default AAnimal constructor called." << std::endl;
}

AAnimal::AAnimal(std::string type): _type(type)
{
	std::cout << " -> Parametric AAnimal constructor called." << std::endl;
}

AAnimal::AAnimal(const AAnimal &src)
{
	std::cout << " -> Copy AAnimal constructor called." << std::endl;
	*this = src;
}

AAnimal::~AAnimal(void)
{
	std::cout << " -> AAnimal destructor called." << std::endl;
}

AAnimal	&AAnimal::operator =(const AAnimal &src)
{
	if (this != &src)
	{
		std::cout << " -> Copy assignment AAnimal called." << std::endl;
		this->_type = src._type;
	}
	return *this;
}

std::string	AAnimal::getType(void) const
{
	return this->_type;
}

void	AAnimal::makeSound(void) const
{
	std::cout << "As an animal, I don't really have a sound..." << std::endl;
}
