// ex00 BitcoinExchange : le sujet impose un container STL, ici std::map
// la map est triee par cle automatiquement (red-black tree) donc parfait pour
// retrouver une date avec upper_bound
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <map>   // le container demande par le sujet (date -> taux)
# include <ctime> // pour time_t et struct tm (gestion des dates)

class	BitcoinExchange
{
	private:
		// cle = time_t (timestamp unix), value = float (le taux de change)
		// map garde tout trie par date, c'est ca qu'on veut pour le lower/upper bound
		std::map<time_t, float>	data;
	public:
		// Orthodox Canonical Form demandee par le sujet (ctor, dtor, copy, =)
		~BitcoinExchange(void);
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange &copy);
		float			get_value(time_t time); // retourne le taux pour une date donnee
		BitcoinExchange	&operator=(const BitcoinExchange &copy);
};

#endif
