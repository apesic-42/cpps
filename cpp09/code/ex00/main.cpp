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

int	main(int argc, char **argv)
{
	BitcoinExchange	db;
	std::ifstream	file;
	std::string		line;
	float			num;
	time_t			timestamp;
	struct tm		timestrct;

	if (argc < 2)
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
	std::getline(file, line);
	while (std::getline(file, line))
	{
		if (line.length() < 14 || line.substr(10, 3) != " | ")
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		if (!parse_date(line.substr(0, 10), &timestrct))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		std::istringstream	iss(line.substr(13));
		iss >> num;
		if (iss.fail())
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		if (num < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue ;
		}
		else if (num > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue ;
		}
		timestamp = mktime(&timestrct);
		float rate = db.get_value(timestamp);
		if (rate < 0)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue ;
		}
		std::cout << line.substr(0, 10) << " => " << num << " = " << num * rate << std::endl;
	}
	file.close();
}
