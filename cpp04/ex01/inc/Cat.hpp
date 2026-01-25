
#ifndef CAT_CLASS_H
# define CAT_CLASS_H

# include <string>
# include "Animal.hpp"

class Cat: public Animal {
private:
	Brain	*_brain;
public:
	Cat(void);
	//Cat(std::string type);
	Cat(const Cat &src);
	virtual ~Cat(void);
	Cat	&operator =(const Cat &src);

	virtual void	makeSound(void) const;
	Brain			*getBrain(void) const;
};

#endif
