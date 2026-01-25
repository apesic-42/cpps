
#include <iostream>
#include <string>
#include "Cat.hpp"

Cat::Cat(void): AAnimal("Cat")
{
	std::cout << " -> Default Cat constructor called." << std::endl;
	this->_brain = new Brain();
}

//Cat::Cat(std::string type): Animal(type)
//{
//	std::cout << " -> Parametric Cat constructor called." << std::endl;
//}

Cat::Cat(const Cat &src): AAnimal(src._type)
{
	std::cout << " -> Copy Cat constructor called." << std::endl;
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
		std::cout << " -> Copy assignment Cat called." << std::endl;
		this->_type = src._type;
		this->_brain->setIdeas(src._brain->getIdeas()); // deep copy
		//this->_brain = src._brain; // shallow copy
	}
	return *this;
}

void	Cat::makeSound(void) const
{
	std::cout << "Imma dominate the world, meow !" << std::endl;
}

Brain	*Cat::getBrain(void) const
{
	return this->_brain;
}
