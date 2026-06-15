
// ex01 : meme Bureaucrat que ex00, mais on ajoute signForm pour faire interagir Bureaucrat et Form
#ifndef BUREAUCRAT_HPP // include guard
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception>
# include "Form.hpp"

class Form; // forward declaration : Form et Bureaucrat se connaissent mutuellement (evite inclusion circulaire)

class Bureaucrat
{
	private:
		const std::string	_name; // const : nom fixe a la construction
		int			_grade; // grade 1 (haut) a 150 (bas)

	public:
		// Constructors & Destructors (forme canonique de coplien)
		Bureaucrat();
		Bureaucrat(std::string name, int grade); // throw si grade hors bornes
		Bureaucrat(const Bureaucrat &other);
		Bureaucrat &operator=(const Bureaucrat &other);
		~Bureaucrat();

		// Member functions
		std::string	getName() const;
		int			getGrade() const;
		void		incrementGrade(); // 1 le plus haut donc on baisse le chiffre
		void		decrementGrade();
		void		signForm(Form &form); // nouveau ex01 : demande la signature d'un form et affiche le resultat

		// Exceptions internes (Bureaucrat::GradeTooHighException etc)
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char *what() const throw(); // throw() = ne lance elle-meme aucune erreur
		};

		class GradeTooLowException : public std::exception
		{
			public:

				virtual const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream & os, Bureaucrat const &other); // operator<< libre

#endif
