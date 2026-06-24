
// ex00 : classe Bureaucrat, le but est d'apprendre les exceptions C++ (try/catch/throw)
#ifndef BUREAUCRAT_HPP // include guard : empeche le header d'etre inclus 2 fois (double definition)
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception> // pour heriter de std::exception (nos classes d'erreur internes)

class Bureaucrat
{
	private:
		const std::string	_name; // const : le nom ne change jamais apres la construction (sujet : name constant)
		int					_grade; // grade entre 1 (le plus haut) et 150 (le plus bas), precise par le sujet

	public:
		// Constructors & Destructors (forme canonique de coplien obligatoire en C++98 a 42)
		Bureaucrat(); // constructeur par defaut
		Bureaucrat(const std::string name, int grade); // constructeur param, peut throw si grade hors bornes
		Bureaucrat(const Bureaucrat &other); // constructeur de copie
		Bureaucrat &operator=(const Bureaucrat &other); // operateur d'affectation
		~Bureaucrat(); // destructeur

		// Member functions
		std::string	getName() const; // const = getter, ne modifie pas l'objet
		int			getGrade() const;
		void		incrementGrade(); // monte le grade (donc le chiffre baisse car 1 est le plus haut)
		void		decrementGrade(); // descend le grade (le chiffre monte)

		// Exceptions : classes imbriquees dans Bureaucrat (sujet : Bureaucrat::GradeTooHighException etc)
		class GradeTooHighException : public std::exception // herite de std::exception pour etre catchable facilement
		{
			public:
				virtual const char *what() const throw(); // throw() = cette fonction en revoie elle-meme pas d'erreur, si y'a une erreur ca fait cracher
				                                          // throw() fait une validation des donner pour ne pas alouer pour r, un peu comme pydentic
		};

		class GradeTooLowException : public std::exception
		{
			public:

				virtual const char *what() const throw(); // redefini le what() de std::exception (methode virtuelle)
		};
};

// operator<< libre (pas membre) pour pouvoir ecrire "cout << bureaucrat", format demander par le sujet
std::ostream &operator<<(std::ostream & os, Bureaucrat const &other);

#endif
