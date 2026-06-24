
#include "Form.hpp"

// les attribut const DOIVENT etre initialiser dans la liste d'initialisation (: ...), pas dans le corps {}
Form::Form() : _name("Default"), _is_signed(false), _sign_grade(150), _execute_grade(150)
{

}

Form::Form(const std::string name, const int sign_grade, const int execute_grade) : _name(name), _is_signed(false), _sign_grade(sign_grade), _execute_grade(execute_grade)
{
	// sujet : les grades du Form suivent les memes regles que ceux du Bureaucrat
	// 1 = plus haut, 150 = plus bas. La validation arrive APRES la liste d'init
	// (les const sont deja initialises) mais le throw interrompt la construction :
	// l'objet Form ne sera jamais "vivant", et _name (string deja construit) est detruit proprement
	if (sign_grade < 1 || execute_grade < 1)
		throw GradeTooHighException(); // grade < 1 = trop haut
	if (sign_grade > 150 || execute_grade > 150)
		throw GradeTooLowException(); // grade > 150 = trop bas
}

// constructeur de copie : on recopie tout, meme les const (autoriser dans la liste d'init seulement)
Form::Form(const Form &other) : _name(other._name), _is_signed(other._is_signed), _sign_grade(other._sign_grade), _execute_grade(other._execute_grade)
{

}

Form &Form::operator=(const Form &other)
{
	_is_signed = other._is_signed; // on copie SEULEMENT _is_signed : le reste est const, impossible a reassigner
	return (*this);
}

Form::~Form()
{

}

// Member function
// beSigned : appeler par Bureaucrat::signForm, c'est le formulaire qui decide s'il accepte la signature
void Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() <= _sign_grade) // grade petit = haut place, donc <= veut dire assez haut
		_is_signed = true;
	else
		throw GradeTooLowException(); // grade trop bas pour signer -> on throw, signForm va catch
}


std::string Form::getName() const
{
	return (_name);
}

bool Form::getIsSigned() const
{
	return (_is_signed);
}

int Form::getSignGrade() const
{
	return (_sign_grade);
}

int Form::getExecuteGrade() const
{
	return (_execute_grade);
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Grade too high!");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Grade too low!");
}


std::ostream &operator<<(std::ostream &os,  Form const &form)
{
	os << "Name: " << form.getName() << " isSigned: " << form.getIsSigned() << " SignGrade: " << form.getSignGrade() << " ExecuteGrade: " << form.getExecuteGrade() << std::endl;
	return (os);
}
