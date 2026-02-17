

#include <iostream>
#include <string>
#include "Cat.hpp"

Cat::Cat(void): Animal("Cat")
{
	std::cout << " -> default Cat constructor called." << std::endl;
	this->_brain = new Brain();
}

Cat::Cat(const Cat &src): Animal(src.type)
{
	std::cout << " -> copy Cat constructor called." << std::endl;
	this->_brain = new Brain();
	*this = src;
}

Cat::~Cat(void)
{
	std::cout << " -> Cat destructor called." << std::endl;
	delete this->_brain;
}

Cat	&Cat::operator =(const Cat &src)
{
	if (this != &src)
	{
		std::cout << " -> copy assignment Cat called." << std::endl;
		this->type = src.type;
		this->_brain->setIdeas(src._brain->getIdeas());
	}
	return *this;
}

void	Cat::makeSound(void) const
{
	std::cout << "Meow !" << std::endl;
}

Brain	*Cat::getBrain(void) const
{
	return this->_brain;
}
