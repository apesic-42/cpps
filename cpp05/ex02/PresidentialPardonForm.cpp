
#include "PresidentialPardonForm.hpp"
#include <string>
// grades du sujet : 25 pour signer, 5 pour executer (les plus exigeants des 3 forms)
PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5), _target("default target")
{

}

PresidentialPardonForm::PresidentialPardonForm(const std::string target) : AForm("PresidentialPardonForm", 25, 5), _target(target)
{

}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other) : AForm(other) // copie la base
{
	*this = other;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
	_target = other._target;
	setIsSigned(other.getIsSigned()); // setter car _is_signed prive dans la base
	return (*this);
}


PresidentialPardonForm::~PresidentialPardonForm()
{

}


// performAction : informe simplement que la cible est pardonnee par Zaphod Beeblebrox (sujet)
void PresidentialPardonForm::performAction() const
{
	std::cout << getName() << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}
