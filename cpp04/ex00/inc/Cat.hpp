#ifndef CAT_CLASS_H
# define CAT_CLASS_H

# include <string>
# include "Animal.hpp"

class Cat: public Animal {
public:
	Cat(void);
	Cat(const Cat &src);
	virtual			~Cat(void);
	Cat &operator	=(const Cat &src);

	virtual void	makeSound(void) const;
};

#endif
