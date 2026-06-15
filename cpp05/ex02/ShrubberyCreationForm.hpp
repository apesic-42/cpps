
// ShrubberyCreationForm : fille concrete de AForm (sign 145 / exec 137 selon le sujet)
#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream> // ofstream pour ecrire dans un fichier (les arbres ASCII)

class ShrubberyCreationForm : public AForm // public AForm = heritage, c'est un AForm
{
	private:
		std::string _target; // la cible : sert a nommer le fichier <target>_shrubbery
		virtual void	performAction() const; // redefini la pure virtuelle de AForm (l'action specifique)

	public:
	// Constructors & Destructors
		ShrubberyCreationForm();
		ShrubberyCreationForm(const std::string target); // un seul parametre : la target (sujet)
		ShrubberyCreationForm(const ShrubberyCreationForm &other);
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
		~ShrubberyCreationForm();

		// exceptions : propre a cette classe (echec d'ouverture du fichier)
		class OpenFileExeption : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

};

#endif
