
#include "ShrubberyCreationForm.hpp"
#include <string>
// on appelle le constructeur de la base AForm avec les grades du sujet : 145 pour signer, 137 pour exec
ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137), _target("default target")
{

}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target) : AForm("ShrubberyCreationForm", 145, 137), _target(target)
{

}

// constructeur de copie : on copie d'abord la partie base AForm(other), puis le reste via operator=
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(other)
{
	*this = other;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	_target = other._target;
	setIsSigned(other.getIsSigned()); // on passe par le setter car _is_signed est prive dans la base
	return (*this);
}


ShrubberyCreationForm::~ShrubberyCreationForm()
{

}


// performAction : l'action specifique de ce form, appeler par AForm::execute (apres verif signe+grade)
void ShrubberyCreationForm::performAction() const
{
	std::ofstream outFile((_target + std::string("_shrubbery")).c_str()); // ofstream pour creer/ecrire le fichier <target>_shrubbery ; .c_str() car ofstream C++98 veut un const char*

	if (outFile) // si le fichier s'est bien ouvert
	{
		outFile << "    /\\    \n";
		outFile << "   /  \\   \n";
		outFile << "  /    \\  \n";
		outFile << " /      \\ \n";
		outFile << "/________\\\n";
		outFile << "    ||    \n";
		outFile << "    ||    \n";
		outFile << "    ||    \n";

		outFile.close(); // on ferme le fichier proprement
	}
	else
		throw ShrubberyCreationForm::OpenFileExeption(); // ouverture echouee -> on throw

}

const char *ShrubberyCreationForm::OpenFileExeption::what() const throw()
{
	return ("Could not open and write the file!");
}
