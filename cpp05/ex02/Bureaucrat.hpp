
// ex02 : Bureaucrat parle maintenant a AForm (abstrait), et gagne executeForm
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
		int			_grade; // 1 a 150

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
		void		signForm(AForm &form); // demande la signature d'un form
		void		executeForm(const AForm &form) const; // nouveau ex02 : demande l'execution d'un form

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
