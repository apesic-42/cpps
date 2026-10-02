// la map est triee par cle automatiquement (red-black tree) donc parfait pour retrouver une date avec upper_bound
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <map>    // le container demande par le sujet (date -> taux)
# include <ctime>  // pour time_t et struct tm (gestion des dates)
# include <string>

class	BitcoinExchange
{
	private:
		// cle = time_t (timestamp unix), value = double (le taux de change)
		// map garde tout trie par date, c'est ca qu'on veut pour le lower/upper bound
		// double et pas float : 1000 * 47115.93 en float s'affichait 4.71159e+07
		std::map<time_t, double>	data;
	public:
		// Orthodox Canonical Form demandee par le sujet (ctor, dtor, copy, =)
		~BitcoinExchange(void);
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange	&operator=(const BitcoinExchange &copy);
		double			get_value(time_t time); // retourne le taux pour une date donnee
		// parse "YYYY-MM-DD" en struct tm. static = pas besoin d'objet pour l'appeler,
		static bool		parse_date(const std::string &str, struct tm *t);
};

#endif
