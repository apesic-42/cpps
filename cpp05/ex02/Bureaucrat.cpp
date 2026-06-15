
#include "Bureaucrat.hpp"
#include "AForm.hpp"

// Constructors & Destructors
Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) // 150 = plus bas
{

}

Bureaucrat::Bureaucrat(const std::string name, int grade) : _name(name) // const init en liste
{
	if (grade < 1) // 1 est le plus haut, impossible de monter au dessus
		throw GradeTooHighException();
	else if (grade > 150) // 150 est le plus bas
		throw GradeTooLowException();
	else
		_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade)
{

}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
	if (this != &other) // protection auto-affectation
		_grade = other._grade; // _name const, pas copie
	return (*this);
}

Bureaucrat::~Bureaucrat()
{

}

// Member functions
std::string Bureaucrat::getName() const
{
	return (_name);
}

int Bureaucrat::getGrade() const
{
	return (_grade);
}



void Bureaucrat::decrementGrade() // augmente le chiffre vers 150
{
	if (_grade == 150) // deja au min
		throw GradeTooLowException();
	else
		_grade++;
}

void Bureaucrat::incrementGrade() // baisse le chiffre vers 1
{
	if (_grade == 1) // deja au max
		throw GradeTooHighException();
	else
	_grade--;
}

// signForm : demande la signature, affiche succes ou echec avec la raison
void Bureaucrat::signForm(AForm &form)
{
	try
	{
		form.beSigned(*this); // le form verifie le grade et throw si insuffisant
	}
	catch(const std::exception& e)
	{
		std::cout << _name << " couldn't sign " << form.getName() << " because " << e.what() << std::endl;
		return; // on sort pour ne pas afficher le succes en dessous
	}
	std::cout << _name << " signed " << form.getName() << std::endl;
}

// executeForm : demande l'execution, AForm::execute throw si pas signe ou grade insuffisant
void Bureaucrat::executeForm(const AForm &form) const
{
	try
	{
		form.execute(*this); // appel polymorphe vers la bonne action (Shrubbery/Robotomy/Presidential)
		std::cout << _name << " executed " << form.getName() << std::endl; // affiche que si pas d'exception
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n'; // affiche la raison de l'echec
	}
}

// operator<< format sujet "<name>, bureaucrat grade <grade>."
std::ostream &operator<<(std::ostream &os, Bureaucrat const &other)
{
	os << other.getName() << ", bureaucrat grade " << other.getGrade() << std::endl;
	return (os);
}

// Exceptions
const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade too high!");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade too low!");
}
