
#include <iostream>
#include <string>
#include "AAnimal.hpp"

AAnimal::AAnimal(void): type("AAnimal")
{
	std::cout << " -> default AAnimal constructor called." << std::endl;
}

AAnimal::AAnimal(std::string type): type(type)
{
	std::cout << " -> parametric AAnimal constructor called." << std::endl;
}

AAnimal::AAnimal(const AAnimal &src)
{
	std::cout << " -> copy AAnimal constructor called." << std::endl;
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
		std::cout << " -> copy assignment AAnimal called." << std::endl;
		this->type = src.type;
	}
	return *this;
}

std::string	AAnimal::getType(void) const
{
	return this->type;
}

void	AAnimal::makeSound(void) const
{
	std::cout << "As an animal, I don't really have a sound..." << std::endl;
}
