
// ShrubberyCreationForm : fille concrete de AForm (sign 145 / exec 137 selon le sujet)
#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream> // ofstream pour ecrire le fichier <target>_shrubbery

class ShrubberyCreationForm : public AForm
{
	private:
		std::string _target; // cible -> nom du fichier
		virtual void	performAction() const; // redefini la pure virtuelle de AForm

	public:
	// Constructors & Destructors
		ShrubberyCreationForm();
		ShrubberyCreationForm(const std::string target); // un seul parametre : la target
		ShrubberyCreationForm(const ShrubberyCreationForm &other);
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
		~ShrubberyCreationForm();

		// exceptions : echec d'ouverture du fichier
		class OpenFileExeption : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

};

#endif
