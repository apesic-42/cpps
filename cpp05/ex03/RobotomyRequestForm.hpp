
// RobotomyRequestForm : fille concrete de AForm (sign 72 / exec 45 selon le sujet)
#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <fstream>
#include <stdlib.h>     /* srand, rand : pour le 50% de reussite aleatoire */
#include <time.h>       /* time */

class RobotomyRequestForm : public AForm
{
	private:
		std::string		_target; // cible a robotomiser
		virtual void	performAction() const; // redefini la pure virtuelle de AForm

	public:
	// Constructors & Destructors
		RobotomyRequestForm();
		RobotomyRequestForm(const std::string target); // un seul parametre : la target
		RobotomyRequestForm(const RobotomyRequestForm &other);
		RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
		~RobotomyRequestForm();

		// exceptions : la robotomie a echoue (1 fois sur 2)
		class RobotizationFailed : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

#endif
