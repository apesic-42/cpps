
#include "ShrubberyCreationForm.hpp"
#include <string>
// 145 pour signer, 137 pour exec : valeurs imposees par le sujet pour ce form
ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137)
{

}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target) : AForm("ShrubberyCreationForm", 145, 137), _target(target)
{

}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(other) // copie la base d'abord
{
	*this = other;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	_target = other._target;
	setIsSigned(other.getIsSigned()); // setter car _is_signed prive dans la base
	return (*this);
}


ShrubberyCreationForm::~ShrubberyCreationForm()
{

}


// performAction : ecrit des arbres ASCII dans le fichier <target>_shrubbery
void ShrubberyCreationForm::performAction() const
{
	std::ofstream outFile((_target + std::string("_shrubbery")).c_str()); // ofstream = ecriture fichier ; .c_str() car C++98

	if (outFile) // ouverture reussie
	{
		outFile << "    /\\    \n";
		outFile << "   /  \\   \n";
		outFile << "  /    \\  \n";
		outFile << " /      \\ \n";
		outFile << "/________\\\n";
		outFile << "    ||    \n";
		outFile << "    ||    \n";
		outFile << "    ||    \n";

		outFile.close(); // fermeture propre
	}
	else
		throw ShrubberyCreationForm::OpenFileExeption(); // echec ouverture -> throw

}

const char *ShrubberyCreationForm::OpenFileExeption::what() const throw()
{
	return ("Could not open and write the file!");
}
