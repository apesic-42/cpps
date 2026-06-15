
#include "Bureaucrat.hpp"

// Constructors & Destructors
// les attributs const (_name) DOIVENT etre initialiser dans la liste d'init (: ...), pas dans le corps {}
Bureaucrat::Bureaucrat() : _name("default"), _grade(150) // grade 150 par defaut = le plus bas
{

}

Bureaucrat::Bureaucrat(const std::string name, int grade) : _name(name)
{
	if (grade < 1) // grade < 1 impossible car 1 est le plus haut -> on throw
		throw GradeTooHighException();
	else if (grade > 150) // grade > 150 impossible car 150 est le plus bas -> on throw
		throw GradeTooLowException();
	else
		_grade = grade; // grade valide (1-150 comme preciser par le sujet), on l'assigne
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade) // copie tout
{

}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) // not the name (name is const, const can't be update)
{
	if (this != &other) // protection contre l'auto-affectation (a = a)
		_grade = other._grade; // on copie SEULEMENT le grade, le name est const donc impossible
	return (*this); // return *this pour pouvoir chainer (a = b = c)
}


Bureaucrat::~Bureaucrat() // rien a liberer (pas d'allocation dynamique)
{

}

// Member functions
std::string Bureaucrat::getName() const // getter du name
{
	return (_name);
}

int Bureaucrat::getGrade() const // getter du grade
{
	return (_grade);
}

void Bureaucrat::incrementGrade() // 1 is highest, 150 lowerest
{
	if (_grade == 1) // deja au plus haut, impossible de monter encore -> throw
		throw GradeTooHighException();
	else
	_grade--; // incrementer le grade = baisser le chiffre (3 -> 2) car 1 est le plus haut
}

void Bureaucrat::decrementGrade()
{
	if (_grade == 150) // deja au plus bas, impossible de descendre encore -> throw
		throw GradeTooLowException();
	else
		_grade++; // decrementer = augmenter le chiffre vers 150
}

// operator<< : format exact demande par le sujet "<name>, bureaucrat grade <grade>."
std::ostream &operator<<(std::ostream &os, Bureaucrat const &other)
{
	os << other.getName() << ", bureaucrat grade " << other.getGrade() << std::endl;
	return (os); // return le stream pour pouvoir chainer les <<
}

// Exceptions : redefinition de what() pour chaque classe d'erreur, renvoie juste un message
const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade too high!");
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade too low!");
}
