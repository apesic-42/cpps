
#ifndef DOG_CLASS_H
# define DOG_CLASS_H

# include <string>
# include "AAnimal.hpp"

class Dog: public AAnimal {
private:
	Brain	*_brain;
public:
	Dog(void);
	//Dog(std::string type);
	Dog(const Dog &src);
	virtual ~Dog(void);
	Dog	&operator =(const Dog &src);

	virtual void	makeSound(void) const;
	Brain			*getBrain(void) const;
};

#endif
