
// ex03 : meme AForm abstrait que ex02 (le A = classe abstraite, convention 42)
#ifndef AForm_HPP
# define AForm_HPP

#include <string>
#include <exception>
#include "Bureaucrat.hpp"
#include <ostream>

class Bureaucrat; // forward declaration

class AForm
{
	private:
		const std::string 	_name; // const : nom du form
		bool				_is_signed; // false au depart
		const int			_sign_grade; // const : grade requis pour signer
		const int			_execute_grade; // const : grade requis pour executer
		virtual void	performAction() const = 0; // = 0 -> pure virtuelle, rend AForm abstraite (pas instanciable)

	public:
		// Constructors & Destructors
		AForm();
		AForm(const std::string name, const int sign_grade, const int execute_grade);
		AForm(const AForm &other);
		AForm &operator=(const AForm &other);
		virtual ~AForm(); // destructeur VIRTUEL : ex03 stocke les forms via AForm* (Intern), il faut le bon destructeur a la suppression

		// Member fonctions
		void			beSigned(const Bureaucrat &bureaucrat);
		std::string 	getName() const;
		bool			getIsSigned() const;
		int				getSignGrade() const;
		int				getExecuteGrade() const;
		void			setIsSigned(bool is_signed); // setter pour les filles
		void			execute(const Bureaucrat &executor) const; // verif signe+grade puis performAction

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

		class IsNotSignedException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream &os,  AForm const &AForm);

#endif
