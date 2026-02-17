
#ifndef WRONGANIMAL_CLASS_H
# define WRONGANIMAL_CLASS_H

# include <string>

class WrongAnimal {
protected:
	std::string	type;

public:
	WrongAnimal(void);
	WrongAnimal(std::string type);
	WrongAnimal(const WrongAnimal &src);
	virtual					~WrongAnimal(void);
	WrongAnimal &operator	=(const WrongAnimal &src);

	std::string				getType(void) const;
	void					makeSound(void) const;
};

#endif
