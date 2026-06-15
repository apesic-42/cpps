
#ifndef FORM_HPP // include guard, evite que le header soit inclus 2 fois (double definition)
# define FORM_HPP

#include <string>
#include <exception> // pour heriter de std::exception (nos classes d'erreur)
#include "Bureaucrat.hpp"
#include <ostream> // pour la surcharge de operator<<

class Bureaucrat; // forward declaration : on dit "cette classe existe" sans l'inclure (evite inclusion circulaire Form<->Bureaucrat)

// ex01 : la classe Form, attributs TOUS prives (encapsulation stricte demander par le sujet)
class Form
{
	private:
		const std::string 	_name; // const : le nom du formulaire ne change jamais apres construction
		bool				_is_signed; // false a la construction (sujet : pas signe au depart)
		const int			_sign_grade; // const : grade requis pour signer, fixe a la construction
		const int			_execute_grade; // const : grade requis pour executer

	public:
		// Constructors & Destructors (forme canonique de coplien : default, param, copy, =, destructeur)
		Form();
		Form(const std::string name, const int sign_grade, const int execute_grade);
		Form(const Form &other);
		Form &operator=(const Form &other);
		~Form();

		// Member fonctions
		void		beSigned(const Bureaucrat &bureaucrat); // passe _is_signed a true si le grade suffit, sinon throw
		std::string getName() const; // const = ne modifie pas l'objet (getter)
		bool		getIsSigned() const;
		int			getSignGrade() const;
		int			getExecuteGrade() const;

		// exceptions internes, comme dans ex00 (Form::GradeTooHighException etc)
		class GradeTooHighException : public std::exception // herite de std::exception pour etre catchable facilement
		{
			public:
				virtual const char *what() const throw(); // throw() = cette fonction ne lance elle-meme aucune erreur
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream &os,  Form const &form); // operator<< libre (pas membre) pour pouvoir ecrire "cout << form"

#endif
