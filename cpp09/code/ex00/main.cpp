#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>  // istringstream pour parser date et valeur
#include <cstdlib>
#include <cstring>  // memset

// meme fonction que dans le .cpp (re-declaree ici car static = locale au fichier)
// parse "YYYY-MM-DD" en struct tm, voir explications dans BitcoinExchange.cpp
static bool	parse_date(const std::string &str, struct tm *t)
{
	int	year, month, day;
	char dash1, dash2;

	if (str.length() != 10)
		return (false);
	std::istringstream iss(str);
	iss >> year >> dash1 >> month >> dash2 >> day;
	if (iss.fail() || dash1 != '-' || dash2 != '-')
		return (false);
	if (month < 1 || month > 12 || day < 1 || day > 31)
		return (false);
	std::memset(t, 0, sizeof(struct tm)); // zero-init obligatoire avant mktime
	t->tm_year = year - 1900;
	t->tm_mon = month - 1;
	t->tm_mday = day;
	return (true);
}

int	main(int argc, char **argv)
{
	BitcoinExchange	db; // le ctor charge data.csv tout seul
	std::ifstream	file;
	std::string		line;
	float			num;       // la valeur lue sur chaque ligne
	time_t			timestamp; // la date convertie en timestamp
	struct tm		timestrct;

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
	std::getline(file, line); // skip le header du fichier d'entree
	while (std::getline(file, line))
	{
		// le sujet impose le format "date | value". substr(10,3) doit valoir " | "
		if (line.length() < 14 || line.substr(10, 3) != " | ")
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		if (!parse_date(line.substr(0, 10), &timestrct)) // 10 premiers char = date
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		// la valeur commence apres " | " donc a la position 13 (10 + 3)
		std::istringstream	iss(line.substr(13));
		iss >> num; // on tente de lire un float
		if (iss.fail()) // pas un nombre = bad input
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		if (num < 0) // le sujet refuse les valeurs negatives
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
		float rate = db.get_value(timestamp); // taux de la date la plus proche
		if (rate < 0) // -1 = date trop ancienne, pas dans la base
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		// resultat = valeur * taux du jour, comme demande par le sujet
		std::cout << line.substr(0, 10) << " => " << num << " = " << num * rate << std::endl;
	}
	file.close();
}
