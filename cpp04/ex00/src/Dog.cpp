

#include <iostream>
#include <string>
#include "Dog.hpp"

Dog::Dog(void): Animal("Dog")
{
	std::cout << " -> Default Dog constructor called." << std::endl;
}

//Dog::Dog(std::string type): _type(type)
//{
//	std::cout << " -> Parametric Dog constructor called." << std::endl;
//}

Dog::Dog(const Dog &src): Animal(src._type)
{
	std::cout << " -> Copy Dog constructor called." << std::endl;
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
		std::cout << " -> Copy assignment Dog called." << std::endl;
		this->_type = src._type;
	}
	return *this;
}

void	Dog::makeSound(void) const
{
	std::cout << "Imma bark... Woof Woof !" << std::endl;
}
