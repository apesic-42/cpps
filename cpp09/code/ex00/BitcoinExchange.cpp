#include "BitcoinExchange.hpp"
#include <fstream>  // std::ifstream pour lire data.csv et le fichier d'entree
#include <iostream>
#include <sstream>  // std::istringstream pour parser les dates / valeurs
#include <cstdlib>  // atof / exit (versions C, compatibles C++98)
#include <cstring>  // std::memset

// parse une date "YYYY-MM-DD" en struct tm. static = visible que dans ce fichier
// on parse a la main car std::get_time est C++11 et le sujet impose C++98
static bool	parse_date(const std::string &str, struct tm *t)
{
	int	year, month, day;
	char dash1, dash2;     // les deux tirets attendus dans la date

	if (str.length() != 10) // une date valide fait pile 10 char (YYYY-MM-DD)
		return (false);
	std::istringstream iss(str); // stringstream pour extraire les morceaux
	iss >> year >> dash1 >> month >> dash2 >> day; // lit dans l'ordre du format
	if (iss.fail() || dash1 != '-' || dash2 != '-') // format casse = on rejette
		return (false);
	if (month < 1 || month > 12 || day < 1 || day > 31) // plages valides
		return (false);
	std::memset(t, 0, sizeof(struct tm)); // remet tout a 0 sinon mktime delire
	t->tm_year = year - 1900; // tm_year compte depuis 1900 (convention posix)
	t->tm_mon = month - 1;    // tm_mon va de 0 a 11
	t->tm_mday = day;
	return (true);
}

BitcoinExchange::~BitcoinExchange(void)
{
}

// le constructeur charge directement data.csv dans la map (date -> taux)
BitcoinExchange::BitcoinExchange(void)
{
	std::ifstream	file;
	std::string		line;
	struct tm		timestrct;

	file.open("data.csv"); // la base de donnees fournie par le sujet
	if (!file.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		exit(1); // sans la base on peut rien faire, on quitte
	}
	std::getline(file, line); // on jette la 1ere ligne (header "date,exchange_rate")
	while (std::getline(file, line)) // on lit ligne par ligne jusqu'a la fin
	{
		if (line.length() < 12) // date(10) + virgule + au moins 1 chiffre
			continue ;
		if (!parse_date(line.substr(0, 10), &timestrct)) // 10 premiers char = date
			continue ; // date pourrie on saute la ligne
		// mktime transforme le struct tm en time_t (timestamp), c'est notre cle
		// atof parse le taux (apres la virgule, position 11). atof = C++98 friendly
		data.insert(std::pair<time_t, float>(mktime(&timestrct), atof(line.substr(11).c_str())));
	}
	file.close();
}

// constructeur de copie : on recopie juste la map, pas besoin de relire le csv
BitcoinExchange::BitcoinExchange(BitcoinExchange &copy)
{
	data = copy.data;
}

// retrouve le taux pour une date donnee (ou la date inferieure la plus proche)
float	BitcoinExchange::get_value(time_t time)
{
	std::map<time_t, float>::iterator	it;

	// upper_bound = 1er element STRICTEMENT superieur a time. c'est l'interet
	// de la map : elle est triee donc cette recherche est en O(log n)
	it = data.upper_bound(time);
	if (it == data.begin()) // date plus ancienne que toute la base
		return (-1);        // -1 = signal d'erreur (decrementer begin serait UB)
	it--; // on recule d'un cran : on tombe sur la date <= time la plus proche
	return (it->second); // second = la value de la paire = le taux
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this != &copy) // protection contre l'auto-affectation (a = a)
		data = copy.data;
	return (*this);
}
