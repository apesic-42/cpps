
// ex03 : l'Intern, une classe sans nom ni grade (juste une factory de forms)
#ifndef INTERN_HPP
# define INTERN_HPP

# include <iostream>
# include <string>
# include <exception>
# include "AForm.hpp"

class AForm; // forward declaration

class Intern
{
	private:
		// aucun attribut : l'Intern n'a ni nom ni grade (sujet)

	public:
		// Constructors & Destructors (forme canonique meme si la classe est "vide")
		Intern();
		Intern(const Intern &other);
		Intern &operator=(const Intern &other);
		~Intern();

		// Member functions
		// makeForm : retourne un AForm* du bon type selon form_name, avec la target initialisee
		AForm	*makeForm(const std::string form_name, const std::string form_target) ;
};

#endif
