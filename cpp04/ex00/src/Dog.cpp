

#include <iostream>
#include <string>
#include "Dog.hpp"

Dog::Dog(void): Animal("Dog")
{
	std::cout << " -> default Dog constructor called." << std::endl;
}

Dog::Dog(const Dog &src): Animal(src.type)
{
	std::cout << " -> copy Dog constructor called." << std::endl;
	*this = src;
}

Dog::~Dog(void)
{
	std::cout << " -> Dog destructor called." << std::endl;
}

Dog	&Dog::operator =(const Dog &src)
{
	if (this != &src)
	{
		std::cout << " -> copy assignment Dog called." << std::endl;
		this->type = src.type;
	}
	return *this;
}

void	Dog::makeSound(void) const
{
	std::cout << "Woof Woof !" << std::endl;
}
