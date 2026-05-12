
#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

// Constructors & Destructors
Intern::Intern()
{

}

Intern::Intern(const Intern &other)
{
	(void) other;
}

Intern &Intern::operator=(const Intern &other)
{
	(void) other;
	return (*this);
}

Intern::~Intern()
{

}

// Member functions
AForm *Intern::makeForm(const std::string form_name, const std::string form_target)
{
	int i = 0;
	std::string available_forms[] = {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};

	while (i < 3 && form_name != available_forms[i])
		i++;

	switch (i)
	{
	case 0:
		std::cout << "Intern creates " << form_name << std::endl;
		return (new ShrubberyCreationForm(form_target));
	case 1:
		std::cout << "Intern creates " << form_name << std::endl;
		return (new RobotomyRequestForm(form_name));
	case 2:
		std::cout << "Intern creates " << form_name << std::endl;
		return (new PresidentialPardonForm (form_target));
	default:
		std::cout << "Form is not existing" << std::endl;
		return NULL;
	}
}
