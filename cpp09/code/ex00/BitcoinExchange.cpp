#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>

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
	std::memset(t, 0, sizeof(struct tm));
	t->tm_year = year - 1900;
	t->tm_mon = month - 1;
	t->tm_mday = day;
	return (true);
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(void)
{
	std::ifstream	file;
	std::string		line;
	struct tm		timestrct;

	file.open("data.csv");
	if (!file.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		exit(1);
	}
	std::getline(file, line);
	while (std::getline(file, line))
	{
		if (line.length() < 12)
			continue ;
		if (!parse_date(line.substr(0, 10), &timestrct))
			continue ;
		data.insert(std::pair<time_t, float>(mktime(&timestrct), atof(line.substr(11).c_str())));
	}
	file.close();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange &copy)
{
	data = copy.data;
}

float	BitcoinExchange::get_value(time_t time)
{
	std::map<time_t, float>::iterator	it;

	it = data.upper_bound(time);
	if (it == data.begin())
		return (-1);
	it--;
	return (it->second);
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this != &copy)
		data = copy.data;
	return (*this);
}
