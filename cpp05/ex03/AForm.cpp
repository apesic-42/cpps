
#include "AForm.hpp"

// const init en liste obligatoire
AForm::AForm() : _name("Default"), _is_signed(false), _sign_grade(150), _execute_grade(150)
{

}

AForm::AForm(const std::string name, const int sign_grade, const int execute_grade) : _name(name), _is_signed(false), _sign_grade(sign_grade), _execute_grade(execute_grade)
{

}

AForm::AForm(const AForm &other) : _name(other._name), _is_signed(other._is_signed), _sign_grade(other._sign_grade), _execute_grade(other._execute_grade)
{

}

AForm &AForm::operator=(const AForm &other)
{
	_is_signed = other._is_signed; // seul attribut non-const copiable
	return (*this);
}

AForm::~AForm() // virtuel (declare dans le hpp) pour la suppression correcte via AForm*
{

}

// Member function
void AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() <= _sign_grade) // petit chiffre = haut grade
		_is_signed = true;
	else
		throw GradeTooLowException();
}


std::string AForm::getName() const
{
	return (_name);
}

bool AForm::getIsSigned() const
{
	return (_is_signed);
}

int AForm::getSignGrade() const
{
	return (_sign_grade);
}

int AForm::getExecuteGrade() const
{
	return (_execute_grade);
}

void AForm::setIsSigned(bool is_signed) // setter pour les filles (attribut prive dans la base)
{
	_is_signed = is_signed;
}

// execute : verif communes puis appel polymorphe a performAction (specifique a chaque fille)
void AForm::execute(const Bureaucrat &executor) const
{
	if (_is_signed == false) // pas signe -> pas executable
		throw IsNotSignedException();
	if (_execute_grade < executor.getGrade()) // grade requis < grade executeur => trop bas
		throw GradeTooLowException();

	performAction(); // la bonne version selon le vrai type de l'objet
}


const char *AForm::GradeTooHighException::what() const throw()
{
	return ("Grade too high!");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("Grade too low!");
}

const char *AForm::IsNotSignedException::what() const throw()
{
	return ("Form can not be executed, because it is not signed!");
}

// operator<< : affiche les infos du form
std::ostream &operator<<(std::ostream &os,  AForm const &AForm)
{
	os << "Name: " << AForm.getName() << " isSigned: " << AForm.getIsSigned() << " SignGrade: " << AForm.getSignGrade() << " ExecuteGrade: " << AForm.getExecuteGrade() << std::endl;
	return (os);
}

