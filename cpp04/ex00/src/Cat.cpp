

#include <iostream>
#include <string>
#include "Cat.hpp"

Cat::Cat(void): Animal("Cat")
{
	std::cout << " -> default Cat constructor called." << std::endl;
}

Cat::Cat(const Cat &src): Animal(src.type)
{
	std::cout << " -> copy Cat constructor called." << std::endl;
	*this = src;
}

Cat::~Cat(void)
{
	std::cout << " -> Cat destructor called." << std::endl;
}

Cat	&Cat::operator =(const Cat &src)
{
	if (this != &src)
	{
		std::cout << " -> copy assignment Cat called." << std::endl;
		this->type = src.type;
	}
	return *this;
}

void	Cat::makeSound(void) const
{
	std::cout << "Meow !" << std::endl;
}
