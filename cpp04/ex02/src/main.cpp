

#include <iostream>
#include <string>
#include <string.h>
#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int	main()
{
	AAnimal	*cat = new Cat();
	cat->makeSound();

	delete cat;

	return 0;
}
