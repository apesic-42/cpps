
#include <iostream>
#include <string>
#include <string.h>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

void	tests_pointers(void)
{
	// Brain deep copy (heap)
	Brain	*hermine = new Brain();

	{
		Brain	*leo = new Brain();
		leo->setIdea("great idea", 0);
		*hermine = *leo;
		leo->setIdea("another great idea", 0);
		Brain	*tomme = new Brain(*leo);
		leo->setIdea("bad idea", 0);
		std::cout << "leo 1st idea: " << leo->getIdeas()[0] << std::endl;
		delete leo;
		std::cout << "tomme 1st idea: " << tomme->getIdeas()[0] << std::endl;
		delete tomme;
	}
	std::cout << "hermine 1st idea: " << hermine->getIdeas()[0] << std::endl;
	delete hermine;
	std::cout << std::endl << std::endl;

	// Cat deep copy (heap)
	Cat	*leo = new Cat();

	{
		Cat	*mala = new Cat();
		mala->getBrain()->setIdea("great idea", 0);
		*leo = *mala;
		mala->getBrain()->setIdea("another great idea", 0);
		Cat	*saso = new Cat(*mala);
		mala->getBrain()->setIdea("bad idea", 0);
		std::cout << "mala 1st idea: " << mala->getBrain()->getIdeas()[0] << std::endl;
		delete mala;
		std::cout << "saso 1st idea: " << saso->getBrain()->getIdeas()[0] << std::endl;
		delete saso;
	}
	std::cout << "Leo 1st idea: " << leo->getBrain()->getIdeas()[0] << std::endl;
	delete leo;
	std::cout << std::endl << std::endl;

	// Dog deep copy (heap)
	Dog	*timal = new Dog();

	{
		Dog	*sdm = new Dog();
		sdm->getBrain()->setIdea("great idea", 0);
		*timal = *sdm;
		sdm->getBrain()->setIdea("another great idea", 0);
		Dog	*rapta = new Dog(*sdm);
		sdm->getBrain()->setIdea("bad idea", 0);
		std::cout << "sdm 1st idea: " << sdm->getBrain()->getIdeas()[0] << std::endl;
		delete sdm;
		std::cout << "rapta 1st idea: " << rapta->getBrain()->getIdeas()[0] << std::endl;
		delete rapta;
	}
	std::cout << "timal 1st idea: " << timal->getBrain()->getIdeas()[0] << std::endl;
	delete timal;
}

void	tests(void)
{
	// Brain deep copy (stack)
	Brain	hermine = Brain();

	{
		Brain	leo = Brain();
		leo.setIdea("great idea", 0);
		hermine = leo;
		leo.setIdea("another great idea", 0);
		Brain	tomme = Brain(leo);
		leo.setIdea("bad idea", 0);
		std::cout << "leo 1st idea: " << leo.getIdeas()[0] << std::endl;
		std::cout << "tomme 1st idea: " << tomme.getIdeas()[0] << std::endl;
	}
	std::cout << "hermine 1st idea: " << hermine.getIdeas()[0] << std::endl;
	std::cout << std::endl << std::endl;

	// Cat deep copy (stack)
	Cat	leo = Cat();

	{
		Cat	mala = Cat();
		mala.getBrain()->setIdea("great idea", 0);
		leo = mala;
		mala.getBrain()->setIdea("another great idea", 0);
		Cat	saso = Cat(mala);
		mala.getBrain()->setIdea("bad idea", 0);
		std::cout << "mala 1st idea: " << mala.getBrain()->getIdeas()[0] << std::endl;
		std::cout << "saso 1st idea: " << saso.getBrain()->getIdeas()[0] << std::endl;
	}
	std::cout << "Leo 1st idea: " << leo.getBrain()->getIdeas()[0] << std::endl;
	std::cout << std::endl << std::endl;

	// Dog deep copy (stack)
	Dog	timal = Dog();

	{
		Dog	sdm = Dog();
		sdm.getBrain()->setIdea("great idea", 0);
		timal = sdm;
		sdm.getBrain()->setIdea("another great idea", 0);
		Dog	rapta = Dog(sdm);
		sdm.getBrain()->setIdea("bad idea", 0);
		std::cout << "sdm 1st idea: " << sdm.getBrain()->getIdeas()[0] << std::endl;
		std::cout << "rapta 1st idea: " << rapta.getBrain()->getIdeas()[0] << std::endl;
	}
	std::cout << "timal 1st idea: " << timal.getBrain()->getIdeas()[0] << std::endl;
}

int	main(int argc, char *argv[])
{
	if (argc == 2 && !strcmp(argv[1], "tests"))
	{
		std::cout << "RUN TESTS" << std::endl;
		tests();
		std::cout << std::endl << std::endl;
		tests_pointers();
		return 0;
	}

	std::cout << "RUN PROGRAM" << std::endl << std::endl;

	#define ANIMAL_NUM 5
	Animal *animals[ANIMAL_NUM];

	for (int cur = 0; cur < ANIMAL_NUM; cur++)
	{
		if (cur % 2)
			animals[cur] = new Cat();
		else
			animals[cur] = new Dog();

		animals[cur]->makeSound();
		animals[cur]->getBrain()->setIdea("Don't know...", 0);
		std::cout << "Idea: " << animals[cur]->getBrain()->getIdeas()[0] << std::endl << std::endl;
	}

	std::cout << std::endl;

	for (int cur = 0; cur < ANIMAL_NUM; cur++)
		delete animals[cur];

	return 0;
}
