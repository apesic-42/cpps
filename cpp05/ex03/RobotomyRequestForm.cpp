
#include "RobotomyRequestForm.hpp"
#include <string>
// 72 pour signer, 45 pour exec (valeurs du sujet)
RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45)
{
	srand(time(NULL)); // seed du random base sur l'heure pour avoir un tirage different a chaque execution
}

RobotomyRequestForm::RobotomyRequestForm(const std::string target) : AForm("RobotomyRequestForm", 72, 45), _target(target)
{
	srand(time(NULL));
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(other) // copie la base
{
	*this = other;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	_target = other._target;
	setIsSigned(other.getIsSigned()); // setter car _is_signed prive
	return (*this);
}


RobotomyRequestForm::~RobotomyRequestForm()
{

}


// performAction : robotomise la cible 50% du temps, sinon throw
void RobotomyRequestForm::performAction() const
{
	int random_number;

	random_number = rand() % 2; // 0 ou 1 -> 50/50

	if (random_number == 1)
		std::cout << "Beeep Be Be Beeeee Beeeeeeeep. " << getName() << " has been robotomized successfully!" << std::endl;
	else
		throw RobotizationFailed(); // echec une fois sur deux
}

const char *RobotomyRequestForm::RobotizationFailed::what() const throw()
{
	return ("Unfortunately robotomy failed.");
}
