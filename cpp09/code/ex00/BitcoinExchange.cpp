#include "BitcoinExchange.hpp"
#include <fstream>  // std::ifstream pour lire data.csv et le fichier d'entree
#include <iostream>
#include <cstdlib>  // atof / atoi / exit
#include <cstring>  // memset
#include <cctype>   // isdigit

// nb de jours dans le mois, fevrier depend de l'annee bissextil
static int	days_in_month(int year, int month)
{
	int	days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// bissextile = divisible par 4, sauf les siecles, sauf les multiples de 400
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		return (29);
	return (days[month - 1]);
}

// parse une date "YYYY-MM-DD" en struct tm. false si format ou date invalide
bool	BitcoinExchange::parse_date(const std::string &str, struct tm *t)
{
	int	year, month, day;

	if (str.length() != 10 || str[4] != '-' || str[7] != '-') // pile 10 char, tirets au bon endroit
		return (false);
	for (int i = 0; i < 10; i++) // tout le reste doit etre des chiffres (format strict)
		if (i != 4 && i != 7 && !std::isdigit(str[i]))
			return (false);
	year = std::atoi(str.substr(0, 4).c_str());
	month = std::atoi(str.substr(5, 2).c_str());
	day = std::atoi(str.substr(8, 2).c_str());
	// plages valides. sans le check du mois, 2021-02-29 passait et mktime le transformait en silence en 2021-03-01
	if (month < 1 || month > 12 || day < 1 || day > days_in_month(year, month))
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

	file.open("data.csv");
	if (!file.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		exit(1); // sans la base on peut rien faire, on quitte
	}
	while (std::getline(file, line)) // on lit ligne par ligne jusqu'a la fin
	{
		if (line.length() < 12 || line[10] != ',') // date(10) + virgule + au moins 1 chiffre
			continue ; // le header "date,exchange_rate" saute ici aussi
		if (!parse_date(line.substr(0, 10), &timestrct)) // 10 premiers char = date
			continue ; // date pourrie on saute la ligne
		// mktime transforme le struct tm en time_t (timestamp), c'est notre cle
		// atof parse le taux (apres la virgule, position 11)
		data.insert(std::pair<time_t, double>(mktime(&timestrct), atof(line.substr(11).c_str())));
	}
	file.close();
}

// constructeur de copie : on recopie juste la map, pas besoin de relire le csv
BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	data = copy.data;
}

// retrouve le taux pour une date donnee (ou la date inferieure la plus proche
double	BitcoinExchange::get_value(time_t time)
{
	std::map<time_t, double>::iterator	it;

	//  upper_bound renvoie un itérateur vers le premier element dont la clé est strictement superieur
	// de la map : elle est triee donc cette recherch est en O(log n)
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
