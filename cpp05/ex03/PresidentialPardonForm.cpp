
#include "PresidentialPardonForm.hpp"
#include <string>
// 25 pour signer, 5 pour exec (valeurs du sujet, les plus exigeantes)
PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5)
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
	setIsSigned(other.getIsSigned()); // setter car _is_signed prive
	return (*this);
}


PresidentialPardonForm::~PresidentialPardonForm()
{

}


// performAction : informe que la cible est pardonnee par Zaphod Beeblebrox (sujet)
void PresidentialPardonForm::performAction() const
{
	std::cout << getName() << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}
