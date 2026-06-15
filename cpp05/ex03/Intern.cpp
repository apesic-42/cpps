
#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp" // besoin des classes concretes ici pour pouvoir les "new"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

// Constructors & Destructors
Intern::Intern()
{

}

Intern::Intern(const Intern &other)
{
	(void) other; // (void) pour eviter le warning "unused parameter" : rien a copier (pas d'attribut)
}

Intern &Intern::operator=(const Intern &other)
{
	(void) other; // pareil, rien a affecter
	return (*this);
}

Intern::~Intern()
{

}

// Member functions
// makeForm : factory. On evite la cascade if/elseif/else (interdite par le sujet).
// Idee : un tableau de noms qu'on parcourt pour trouver l'index, puis switch sur l'index.
AForm *Intern::makeForm(const std::string form_name, const std::string form_target)
{
	int i = 0;
	// tableau de noms, l'index donne le bon type de form a creer
	std::string available_forms[] = {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};

	// on avance i tant que le nom ne correspond pas (et qu'on est dans les bornes)
	while (i < 3 && form_name != available_forms[i])
		i++;

	switch (i) // i vaut l'index trouve, ou 3 si non trouve (-> default)
	{
	case 0:
		std::cout << "Intern creates " << form_name << std::endl; // message demande par le sujet
		return (new ShrubberyCreationForm(form_target)); // new car on retourne un pointeur (a delete par l'appelant)
	case 1:
		std::cout << "Intern creates " << form_name << std::endl;
		return (new RobotomyRequestForm(form_target));
	case 2:
		std::cout << "Intern creates " << form_name << std::endl;
		return (new PresidentialPardonForm (form_target));
	default: // nom inconnu
		std::cout << "Form is not existing" << std::endl;
		return NULL; // rien a creer, on rend NULL
	}
}
