
#ifndef WRONGCAT_CLASS_H
# define WRONGCAT_CLASS_H

# include <string>
# include "WrongAnimal.hpp"

class WrongCat: public WrongAnimal {
public:
	WrongCat(void);
	WrongCat(const WrongCat &src);
	virtual				~WrongCat(void);
	WrongCat &operator	=(const WrongCat &src);

	void				makeSound(void) const;
};

#endif
