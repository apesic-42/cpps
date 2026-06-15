
#include "Bureaucrat.hpp"

// main de test : pas de nombre de tests precis dans le sujet, ici on teste les bornes et inc/dec
int main(void)
{
	// les \033[36m / \033[0m sont des codes couleur ANSI (cyan puis reset), juste pour l'affichage
	std::cout << "\033[36m" << std::endl << "Test ex01" << "\033[0m" << std::endl;

	std::cout << "\033[36m" << std::endl << "Test too high and too low creation" << "\033[0m" << std::endl;
	try {
		// 1500 > 150 donc grade trop bas -> le constructeur throw GradeTooLowException
		Bureaucrat Sleeper1 = Bureaucrat("Bernd", 1500);
	}
	catch(const std::exception &e) // on catch tous ce qui herrite de std::exception, donc notament celle qu'on a coder dans hpp
	{
		std::cerr << "Exception caught: " << e.what() << std::endl; // e.what() = le message de l'erreur
	}
	try {
		// -10 < 1 donc grade trop haut -> throw GradeTooHighException
		Bureaucrat Sleeper2 = Bureaucrat("Olaf", -10);
	}
	catch(const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\033[36m" << std::endl << "Test increasing " << "\033[0m" << std::endl;
	Bureaucrat bob = Bureaucrat("Bob", 2); // bob grade 2
	std::cout << bob;

	try {
		bob.incrementGrade(); // 2 -> 1, ok
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << bob;

	try
	{
	bob.incrementGrade(); // deja a 1 (plus haut) -> throw GradeTooHighException
	}
	catch(const std::exception& e)
	{
	std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << bob;



	std::cout << "\033[36m" << std::endl << "Test decreasing" << "\033[0m" << std::endl;
	Bureaucrat tim = Bureaucrat("Tim", 149); // tim grade 149, proche du minimum
	std::cout << tim;
	try
	{
		tim.decrementGrade(); // 149 -> 150, ok
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << tim;

	try
	{
	tim.decrementGrade(); // deja a 150 (plus bas) -> throw GradeTooLowException
	}
	catch(const std::exception& e)
	{
	std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	std::cout << tim;

	return (0);
}
