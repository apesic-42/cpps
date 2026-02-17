

#ifndef ANIMAL_CLASS_H
# define ANIMAL_CLASS_H

# include <string>
# include "Brain.hpp"

class Animal {
protected:
	std::string	type;

public:
	Animal(void);
	Animal(std::string type);
	Animal(const Animal &src);
	virtual ~Animal(void);
	Animal	&operator =(const Animal &src);

	std::string		getType(void) const;
	virtual void	makeSound(void) const;
	virtual Brain	*getBrain(void) const;
};

#endif
