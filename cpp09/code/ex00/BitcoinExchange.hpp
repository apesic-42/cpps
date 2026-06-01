#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <map>
# include <ctime>

class	BitcoinExchange
{
	private:
		std::map<time_t, float>	data;
	public:
		~BitcoinExchange(void);
		BitcoinExchange(void);
		BitcoinExchange(BitcoinExchange &copy);
		float			get_value(time_t time);
		BitcoinExchange	&operator=(const BitcoinExchange &copy);
};

#endif