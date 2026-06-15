
// ex03 : meme Bureaucrat que ex02 (signForm + executeForm), c'est l'Intern qui est la nouveaute
#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception>
# include "AForm.hpp"

class AForm; // forward declaration

class Bureaucrat
{
	private:
		const std::string	_name; // const
		int			_grade; // 1 (haut) a 150 (bas)

	public:
		// Constructors & Destructors
		Bureaucrat();
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat &other);
		Bureaucrat &operator=(const Bureaucrat &other);
		~Bureaucrat();

		// Member functions
		std::string	getName() const;
		int			getGrade() const;
		void		incrementGrade();
		void		decrementGrade();
		void		signForm(AForm &form); // signature d'un form
		void		executeForm(const AForm &form) const; // execution d'un form

		// Exceptions
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:

				virtual const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream & os, Bureaucrat const &other);

#endif
