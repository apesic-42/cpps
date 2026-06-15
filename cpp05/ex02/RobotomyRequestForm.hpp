
// RobotomyRequestForm : fille concrete de AForm (sign 72 / exec 45 selon le sujet)
#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <fstream>
#include <stdlib.h>     /* srand, rand : pour le tirage aleatoire (50% de reussite) */
#include <time.h>       /* time */

class RobotomyRequestForm : public AForm
{
	private:
		std::string		_target; // la cible a robotomiser
		virtual void	performAction() const; // redefini la pure virtuelle de AForm

	public:
	// Constructors & Destructors
		RobotomyRequestForm();
		RobotomyRequestForm(const std::string target); // un seul parametre : la target
		RobotomyRequestForm(const RobotomyRequestForm &other);
		RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
		~RobotomyRequestForm();

		// exceptions : echec de la robotomie (le 50% d'echec du sujet)
		class RobotizationFailed : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

#endif
