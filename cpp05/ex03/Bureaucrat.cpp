
#include "Bureaucrat.hpp"
#include "AForm.hpp"

// Constructors & Destructors
Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) // 150 = plus bas
{

}

Bureaucrat::Bureaucrat(const std::string name, int grade) : _name(name) // const init en liste
{
	if (grade < 1) // 1 le plus haut
		throw GradeTooHighException();
	else if (grade > 150) // 150 le plus bas
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

void Bureaucrat::incrementGrade() // baisse le chiffre vers 1
{
	if (_grade == 1) // deja au max
		throw GradeTooHighException();
	else
	_grade--;
}

void Bureaucrat::decrementGrade() // augmente le chiffre vers 150
{
	if (_grade == 150) // deja au min
		throw GradeTooLowException();
	else
		_grade++;
}

// signForm : affiche succes ou echec avec la raison
void Bureaucrat::signForm(AForm &form)
{
	try
	{
		form.beSigned(*this); // le form throw si grade insuffisant
	}
	catch(const std::exception& e)
	{
		std::cout << _name << " couldn't sign " << form.getName() << " because " << e.what() << std::endl;
		return; // sortie pour ne pas afficher le succes
	}
	std::cout << _name << " signed " << form.getName() << std::endl;
}

// executeForm : execute throw si pas signe ou grade insuffisant
void Bureaucrat::executeForm(const AForm &form) const
{
	try
	{
		form.execute(*this); // appel polymorphe vers la bonne action
		std::cout << _name << " executed " << form.getName() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n'; // raison de l'echec
	}
}

// operator<< format sujet
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
