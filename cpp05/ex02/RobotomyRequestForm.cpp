
#include "RobotomyRequestForm.hpp"
#include <string>
// grades du sujet : 72 pour signer, 45 pour executer
RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45), _target("default target")
{

}

RobotomyRequestForm::RobotomyRequestForm(const std::string target) : AForm("RobotomyRequestForm", 72, 45), _target(target)
{

}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(other) // copie la base d'abord
{
	*this = other;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	_target = other._target;
	setIsSigned(other.getIsSigned()); // setter car _is_signed prive dans la base
	return (*this);
}


RobotomyRequestForm::~RobotomyRequestForm()
{

}


// performAction : bruit de perceuse puis robotomise la cible 50% du temps (sinon echec)
void RobotomyRequestForm::performAction() const
{
	int random_number;

	random_number = rand() % 2; // rand() % 2 donne 0 ou 1 -> 50/50 comme demande par le sujet

	if (random_number == 1)
		std::cout << "Beeep Be Be Beeeee Beeeeeeeep. " << getName() << " has been robotomized successfully!" << std::endl;
	else
		throw RobotizationFailed(); // l'autre moitie du temps : echec, on throw
}

const char *RobotomyRequestForm::RobotizationFailed::what() const throw()
{
	return ("Unfortunately robotomy failed.");
}
