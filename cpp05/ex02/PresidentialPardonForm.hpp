
// PresidentialPardonForm : fille concrete de AForm (sign 25 / exec 5 selon le sujet)
#ifndef PRESIDENTIALFORM_HPP
# define PRESIDENTIALFORM_HPP

#include "AForm.hpp"
#include <fstream>

class PresidentialPardonForm : public AForm
{
	private:
		std::string _target; // la cible a pardonner
		virtual void	performAction() const; // redefini la pure virtuelle de AForm
		// pas d'exception propre ici : l'action ne peut pas echouer (juste un message)

	public:
	// Constructors & Destructors
		PresidentialPardonForm();
		PresidentialPardonForm(const std::string target); // un seul parametre : la target
		PresidentialPardonForm(const PresidentialPardonForm &other);
		PresidentialPardonForm &operator=(const PresidentialPardonForm &other);
		~PresidentialPardonForm();
};

#endif
