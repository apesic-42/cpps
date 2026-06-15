
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

// main de test ex02 : on teste signature + execution des 3 forms concrets
int main(void)
{
	srand(time(NULL)); // initialise le generateur aleatoire (utilise par RobotomyRequestForm)


	std::cout << "\033[36m" << std::endl << "Test ex02" << "\033[0m" << std::endl;

	std::cout << "\033[36m" << std::endl << "Test ex02 ShrubberyCreationForm" << "\033[0m" << std::endl;
	Bureaucrat Mr_Shrubby("Mr_Shrubby", 130); // grade 130 : suffit pour signer (145) et exec (137)
	ShrubberyCreationForm Shrubby_form("Hello"); // target "Hello" -> creera le fichier Hello_shrubbery
	std::cout << std::endl;
	std::cout << Shrubby_form;
	Mr_Shrubby.signForm(Shrubby_form); // signe ok
	std::cout << Shrubby_form;
	Mr_Shrubby.executeForm(Shrubby_form); // execute ok -> ecrit le fichier

	std::cout << "\033[36m" << std::endl << "Test ex02 RobotomyRequestForm" << "\033[0m" << std::endl;
	RobotomyRequestForm Robo_form("I am a robo form");
	Bureaucrat Mr_Robo("Mr_Robo", 45); // grade 45 : juste assez pour exec (45), ok pour signer (72)

	Mr_Robo.executeForm(Robo_form); // pas encore signe -> echec IsNotSignedException
	Mr_Robo.signForm(Robo_form); // signe ok
	Mr_Robo.executeForm(Robo_form); // robotomie : 50% succes 50% echec
	Mr_Robo.executeForm(Robo_form); // on relance plusieurs fois pour voir l'aleatoire
	Mr_Robo.executeForm(Robo_form);

	std::cout << "\033[36m" << std::endl << "Test ex02 PresidentialPardonForm" << "\033[0m" << std::endl;
	PresidentialPardonForm President_form("I am a robo form");
	Bureaucrat Mr_President("Mr_President", 5); // grade 5 : requis pour exec (5), ok pour signer (25)

	Mr_Robo.executeForm(President_form); // Mr_Robo (45) trop bas + pas signe -> echec
	Mr_Robo.signForm(President_form); // Mr_Robo (45) <= 25 ? non -> echec de signature

	Mr_President.executeForm(President_form); // pas signe -> echec
	Mr_President.signForm(President_form); // grade 5 <= 25 -> signe ok
	Mr_President.executeForm(President_form); // grade 5 <= 5 -> exec ok, message de pardon

	return (0);
}
