
#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <iomanip>
# include <sstream>
# include <string>
# include <cctype>
# include <cmath>
# include <limits>

class ScalarConverter
{
private:
	ScalarConverter();
	ScalarConverter(ScalarConverter const &other);
	~ScalarConverter();
	ScalarConverter &operator=(ScalarConverter const &other);

public:
	static void convert(std::string const &value);
};

#endif
