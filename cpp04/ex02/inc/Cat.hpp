

#ifndef CAT_CLASS_H
# define CAT_CLASS_H

# include <string>
# include "AAnimal.hpp"

class Cat: public AAnimal {
private:
	Brain	*_brain;
public:
	Cat(void);
	Cat(const Cat &src);
	virtual ~Cat(void);
	Cat	&operator =(const Cat &src);

	virtual void	makeSound(void) const;
	Brain			*getBrain(void) const;
};

#endif
