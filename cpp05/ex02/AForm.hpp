
// ex02 : Form renomme AForm et rendu ABSTRAIT (le A = convention 42 pour classe abstraite)
#ifndef AForm_HPP // include guard
# define AForm_HPP

#include <string>
#include <exception>
#include "Bureaucrat.hpp"
#include <ostream>

class Bureaucrat; // forward declaration (evite inclusion circulaire AForm<->Bureaucrat)

// classe de base ABSTRAITE : on ne peut pas l'instancier directement, seulement ses filles
class AForm
{
	private:
		// attributs restent PRIVES dans la base (sujet), les filles passent par les getters/setter
		const std::string 	_name; // const : nom du form fixe a la construction
		bool				_is_signed; // false au depart
		const int			_sign_grade; // const : grade requis pour signer
		const int			_execute_grade; // const : grade requis pour executer
		virtual void	performAction() const = 0; // = 0 -> methode pure virtuelle, donc classe abstraite (pas instanciable). Chaque fille la redefini

	public:
		// Constructors & Destructors
		AForm();
		AForm(const std::string name, const int sign_grade, const int execute_grade);
		AForm(const AForm &other);
		AForm &operator=(const AForm &other);
		virtual ~AForm(); // VIRTUEL obligatoire : on manipule les filles via AForm* (polymorphisme).
		                  // sans virtual, delete sur un AForm* n'appelle QUE ~AForm(), pas le destructeur
		                  // de la fille -> comportement indefini / fuite. Regle : base polymorphe = dtor virtuel

		// Member fonctions
		void			beSigned(const Bureaucrat &bureaucrat); // signe si grade suffisant sinon throw
		std::string 	getName() const;
		bool			getIsSigned() const;
		int				getSignGrade() const;
		int				getExecuteGrade() const;
		void			setIsSigned(bool is_signed); // setter utilise par les filles (attributs prives)
		void			execute(const Bureaucrat &executor) const; // verifie signe + grade puis appelle performAction

		// exceptions internes communes a tous les forms
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

		class IsNotSignedException : public std::exception // nouvelle ex02 : form pas signe = pas executable
		{
			public:
				virtual const char *what() const throw();
		};
};

std::ostream &operator<<(std::ostream &os,  AForm const &AForm); // operator<< libre

#endif
