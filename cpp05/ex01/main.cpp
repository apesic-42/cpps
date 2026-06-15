
#include "Bureaucrat.hpp"
#include "Form.hpp"

// main de test ex01 : on reprend les tests de grade puis on teste la signature d'un Form
int main(void)
{
	std::cout << "\033[36m" << std::endl << "Test ex01 :" << "\033[0m" << std::endl;

	std::cout << "\033[36m" << std::endl << "Test too high and too low creation" << "\033[0m" << std::endl;
	try
	{
		Bureaucrat Sleeper1 = Bureaucrat("Bernd", 1500);
	}
	catch(const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	try {
		Bureaucrat Sleeper2 = Bureaucrat("Olaf", -10);
	}
	catch(const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\033[36m" << std::endl << "Test increasing" << "\033[0m" << std::endl;
	Bureaucrat bob = Bureaucrat("Bob", 2);
	std::cout << bob;
	try
	{
		bob.incrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << bob;

	try
	{
	bob.incrementGrade();
	}
	catch(const std::exception& e)
	{
	std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << bob;



	std::cout << "\033[36m" << std::endl << "Test decreasing" << "\033[0m" << std::endl;
	Bureaucrat tim = Bureaucrat("Tim", 149);
	std::cout << tim;
	try
	{
		tim.decrementGrade();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << tim;

	try
	{
	tim.decrementGrade();
	}
	catch(const std::exception& e)
	{
	std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << tim;


	std::cout << "\033[36m" << std::endl << "Test ex01" << "\033[0m" << std::endl;

	Form id_form("ID FORM", 100, 90); // form qui demande grade 100 pour signer, 90 pour executer
	Bureaucrat mr_slow; // bureaucrate par defaut, grade 150 (trop bas pour signer le form)
	Bureaucrat mr_id("MR_ID", 100); // grade 100, juste assez bon pour signer (100 <= 100)
	std::cout << id_form;

	mr_slow.signForm(id_form); // grade 150 > 100 requis -> echec, message "couldn't sign because Grade too low!"
	std::cout << id_form; // isSigned reste a 0

	mr_id.signForm(id_form); // grade 100 <= 100 requis -> succes
	std::cout << id_form; // isSigned passe a 1

	return (0);
}
