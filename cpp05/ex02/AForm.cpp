
#include "AForm.hpp"

// les const (_name, _sign_grade, _execute_grade) DOIVENT etre init dans la liste, pas dans le corps
AForm::AForm() : _name("Default"), _is_signed(false), _sign_grade(150), _execute_grade(150)
{

}

AForm::AForm(const std::string name, const int sign_grade, const int execute_grade) : _name(name), _is_signed(false), _sign_grade(sign_grade), _execute_grade(execute_grade)
{
	// note : les filles appellent ce constructeur avec leurs valeurs (ex 145/137 pour Shrubbery)
	// sujet : les grades suivent les memes regles que le Bureaucrat -> on valide et on throw si hors bornes
	if (sign_grade < 1 || execute_grade < 1)
		throw GradeTooHighException(); // grade < 1 = trop haut (1 est le plus haut)
	if (sign_grade > 150 || execute_grade > 150)
		throw GradeTooLowException(); // grade > 150 = trop bas (150 est le plus bas)
}

AForm::AForm(const AForm &other) : _name(other._name), _is_signed(other._is_signed), _sign_grade(other._sign_grade), _execute_grade(other._execute_grade)
{

}

AForm &AForm::operator=(const AForm &other)
{
	_is_signed = other._is_signed; // seul _is_signed est copiable, le reste est const
	return (*this);
}

AForm::~AForm() // declare virtual dans le hpp -> destruction correcte des filles via AForm*
{

}

// Member function
// beSigned : c'est le form qui decide d'accepter la signature selon le grade du bureaucrate
void AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() <= _sign_grade) // petit chiffre = haut grade, donc <= veut dire assez haut
		_is_signed = true;
	else
		throw GradeTooLowException(); // grade trop bas pour signer
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

void AForm::setIsSigned(bool is_signed) // setter pour que les filles modifient _is_signed (prive dans la base)
{
	_is_signed = is_signed;
}

// execute : logique commune dans la base, verifie les conditions puis delegue a performAction (la partie specifique)
void AForm::execute(const Bureaucrat &executor) const
{
	if (_is_signed == false) // sujet : un form pas signe ne peut pas etre execute
		throw IsNotSignedException();
	if (_execute_grade < executor.getGrade()) // grade requis < grade executeur => executeur trop bas
		throw GradeTooLowException();

	performAction(); // appel polymorphe : la bonne version (Shrubbery/Robotomy/Presidential) selon le vrai type
}


// what() de chaque exception
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

// operator<< : affiche les infos du form (name, signe, grades requis)
std::ostream &operator<<(std::ostream &os,  AForm const &AForm)
{
	os << "Name: " << AForm.getName() << " isSigned: " << AForm.getIsSigned() << " SignGrade: " << AForm.getSignGrade() << " ExecuteGrade: " << AForm.getExecuteGrade() << std::endl;
	return (os);
}

