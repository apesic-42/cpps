
#include <iostream>
#include <string>
#include "Brain.hpp"

Brain::Brain(void)
{
	std::cout << " -> Default Brain constructor called." << std::endl;
}

Brain::Brain(const Brain &src)
{
	std::cout << " -> Copy Brain constructor called." << std::endl;
	*this = src;
}

Brain::~Brain(void)
{
	std::cout << " -> Brain destructor called." << std::endl;
}

Brain	&Brain::operator =(const Brain &src)
{
	if (this != &src)
	{
		std::cout << " -> Copy assignment Brain called." << std::endl;
		for (int i = 0; i < BRAIN_IDEAS_NUM; i++)
			this->ideas[i] = src.ideas[i];
	}
	return *this;
}

const std::string	*Brain::getIdeas(void) const
{
	const std::string	*p_ideas = this->ideas;
	return p_ideas;
}

void	Brain::setIdeas(const std::string *new_ideas)
{
	for (int cur = 0; cur < BRAIN_IDEAS_NUM; cur++)
		this->ideas[cur] = new_ideas[cur];
}

void	Brain::setIdea(std::string idea, int index)
{
	if (index >= 0 && index < BRAIN_IDEAS_NUM)
		this->ideas[index] = idea;
}
