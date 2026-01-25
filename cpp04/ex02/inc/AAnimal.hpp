
#ifndef AANIMAL_CLASS_H
# define AANIMAL_CLASS_H

# include <string>
# include "Brain.hpp"

class AAnimal {
protected:
	std::string	_type;

public:
	AAnimal(void);
	AAnimal(std::string type);
	AAnimal(const AAnimal &src);
	virtual ~AAnimal(void);
	AAnimal	&operator =(const AAnimal &src);

	std::string		getType(void) const;
	virtual void	makeSound(void) const = 0;
};

#endif
