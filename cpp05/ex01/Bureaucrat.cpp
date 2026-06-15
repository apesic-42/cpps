
#include "Bureaucrat.hpp"
#include "Form.hpp"

// Constructors & Desstructors
Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) // 150 = grade le plus bas par defaut
{

}

Bureaucrat::Bureaucrat(const std::string name, int grade) : _name(name) // _name const init en liste
{
	if (grade < 1) // < 1 impossible, 1 est le plus haut
		throw GradeTooHighException();
	else if (grade > 150) // > 150 impossible, 150 est le plus bas
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
		_grade = other._grade; // _name pas copie car const
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

void Bureaucrat::incrementGrade() // monter en grade = baisser le chiffre
{
	if (_grade == 1) // deja au max
		throw GradeTooHighException();
	else
	_grade--;
}

void Bureaucrat::decrementGrade()
{
	if (_grade == 150) // deja au min
		throw GradeTooLowException();
	else
		_grade++;
}

// signForm : le bureaucrate demande la signature, c'est le form (beSigned) qui accepte ou throw
void Bureaucrat::signForm(Form &form)
{
	try
	{
		form.beSigned(*this); // on passe *this (le bureaucrate courant) pour que le form verifie son grade
	}
	catch(const std::exception& e) // si beSigned throw (grade insuffisant), on affiche l'echec avec la raison
	{
		std::cout << _name << " couldn't sign " << form.getName() << " because " << e.what() << std::endl;
		return; // important : on sort, sinon on afficherait aussi le message de succes
	}
	std::cout << _name << " signed " << form.getName() << std::endl; // pas d'exception = succes
}

// operator<< format sujet "<name>, bureaucrat grade <grade>."
std::ostream &operator<<(std::ostream &os, Bureaucrat const &other)
{
	os << other.getName() << ", bureaucrat grade " << other.getGrade() << std::endl;
	return (os);
}

// Exceptions : what() redefini renvoie le message
const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade too high!");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade too low!");
}
