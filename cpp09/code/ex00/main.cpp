#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>  // setprecision
#include <sstream>  // istringstream pour parser la valeur

int	main(int argc, char **argv)
{
	BitcoinExchange	db; // le constructor charge data.csv tout seul
	std::ifstream	file;
	std::string		line;
	std::string		rest;      // ce qui traine apres le nombre (doit etre vide)
	double			num;       // la valeur lue sur chaque ligne
	time_t			timestamp; // la date convertie en timestamp
	struct tm		timestrct;
	bool			first = true;

	if (argc < 2) // il faut le fichier d'entree en argument
	{
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	file.open(argv[1]);
	if (!file.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	// precision par defaut = 6 chiffres : 47115930 s'affichait 4.71159e+07
	std::cout << std::setprecision(10);
	while (std::getline(file, line))
	{
		// on saute le header seulement si c'en est un : avant la 1ere ligne
		// etait jetee a l'aveugle, donc un fichier sans header perdait une donnee
		if (first && line.find("date") != std::string::npos)
		{
			first = false;
			continue ;
		}
		first = false;
		// le sujet impose le format "date | value". substr(10,3) doit valoir " | "
		if (line.length() < 14 || line.substr(10, 3) != " | ")
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		if (!BitcoinExchange::parse_date(line.substr(0, 10), &timestrct)) // 10 premiers char = date
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		// la valeur commence apres " | " donc a la position 13 (10 + 3)
		std::istringstream	iss(line.substr(13));
		iss >> num;
		// pas un nombre, ou un truc qui traine apres ("1 abc", "1.2.3") = bad inpu
		if (iss.fail() || (iss >> rest))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		// le sujet refuse les valeurs negatives. on regarde aussi le signe dans le texte parce que -0 < 0 est faux pour un double
		if (num < 0 || line.substr(13).find('-') != std::string::npos)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue ;
		}
		else if (num > 1000) // et celles au dessus de 1000
		{
			std::cout << "Error: too large a number." << std::endl;
			continue ;
		}
		timestamp = mktime(&timestrct); // struct tm -> time_t pour la recherche
		double rate = db.get_value(timestamp); // taux de la date la plus proche
		if (rate < 0) // -1 = date trop ancienne, pas dans la base
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		// resultat = valeur * taux du jour, comme demande par le sujet
		std::cout << line.substr(0, 10) << " => " << num << " = " << num * rate << std::endl;
	}
	if (file.bad()) // lecture impossible (ex: un repertoire passe en argument)
	{
		std::cout << "Error: could not open file." << std::endl;
		return (1);
	}
	file.close();
}
