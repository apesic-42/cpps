
// ex00 = conversion de type scalaire (char/int/float/double) avec static_cast
// la classe ScalarConverter fait tout le travail dans une seule methode statique

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

// include guard classique (le sujet veut eviter la double inclusion)

# include <iostream> // std::cout pour l'affichage
# include <iomanip>  // formatage des nombres
# include <sstream>  // std::stringstream pour parser la string en nombre
# include <string>   // std::string (le literal arrive en string)
# include <cctype>   // isdigit / isprint pour tester les caracteres
# include <cmath>    // isnan / isinf pour les pseudo-literals
# include <limits>   // std::numeric_limits pour detecter les overflow

class ScalarConverter
{
private:
	// tout en private car le sujet dit que la classe doit pas etre instanciable
	// (forme canonique cachee : pas de construction/copie possible)
	ScalarConverter();
	ScalarConverter(ScalarConverter const &other);
	~ScalarConverter();
	ScalarConverter &operator=(ScalarConverter const &other);

public:
	// static car le sujet impose UNE seule methode statique, sans objet
	// const & = on prend la string sans la copier et on y touche pas
	static void convert(std::string const &value);
};

#endif
