
#include "ScalarConverter.hpp"
#include <cstdlib>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(ScalarConverter const &other) { (void)other; }
ScalarConverter::~ScalarConverter() {}
ScalarConverter &ScalarConverter::operator=(ScalarConverter const &other) { (void)other; return (*this); }

enum Type {
	TypeChar,
	TypeInt,
	TypeFloat,
	TypeDouble,
	TypeLong,
	BadType
};

static int	detectType(std::string const &str, int &ivalue, float &fvalue, double &dvalue, char &cvalue)
{
	std::stringstream ss;
	size_t length = str.length();
	size_t i = 0;
	int type;

	if (length == 1 && !std::isdigit(str[0]))
	{
		cvalue = str[0];
		return (TypeChar);
	}
	if (str[0] == '+' || str[0] == '-')
		ss << str[i++];
	type = TypeInt;
	for ( ; i < length; i++)
	{
		if (str[i] == '.' && type != TypeDouble)
		{
			type = TypeDouble;
			ss << str[i];
		}
		else if (str[i] == 'e' && i < length - 1
			&& (str[i + 1] == '-'
				|| str[i + 1] == '+'
				|| std::isdigit(str[i + 1])))
		{
			ss << str[i] << str[i + 1];
			i++;
			type = TypeDouble;
		}
		else if (str[i] == 'f' && i == length - 1 && type == TypeDouble)
			type = TypeFloat;
		else if (!std::isdigit(str[i]))
		{
			type = BadType;
			i = length;
		}
		else
			ss << str[i];
	}
	if (type == TypeFloat)
		ss >> fvalue;
	else if (type == TypeDouble)
		ss >> dvalue;
	else if (type == TypeInt)
	{
		long lvalue;
		ss >> lvalue;
		ivalue = lvalue;
		if (ss.fail()
			|| lvalue > std::numeric_limits<int>::max()
			|| lvalue < std::numeric_limits<int>::min())
			type = BadType;
	}
	else if (type == BadType)
	{
		if (str == "inff" || str == "-inff" || str == "+inff"
			|| str == "nanf")
		{
			fvalue = atof(str.c_str());
			type = TypeFloat;
		}
		else if (str == "inf" || str == "-inf" || str == "+inf"
				|| str == "nan")
		{
			dvalue = atof(str.c_str());
			type = TypeDouble;
		}
	}
	return (type);
}

void ScalarConverter::convert(std::string const &value)
{
	int		ivalue = 0;
	float	fvalue = 0;
	double	dvalue = 0;
	char	cvalue = 0;
	int		status[4] = {0, 0, 0, 0};

	static const int notPossible = 0x00000001;
	static const int notDisplayable = 0x00000010;

	int type = detectType(value, ivalue, fvalue, dvalue, cvalue);

	if (type != BadType)
	{
		// Convert from detected type to all others
		switch (type)
		{
		case TypeInt:
			fvalue = static_cast<float>(ivalue);
			dvalue = static_cast<double>(ivalue);
			cvalue = static_cast<char>(ivalue);
			break;
		case TypeFloat:
			ivalue = static_cast<int>(fvalue);
			dvalue = static_cast<double>(fvalue);
			cvalue = static_cast<char>(fvalue);
			if (std::isnan(fvalue) || std::isinf(fvalue)
				|| fvalue > std::numeric_limits<int>::max()
				|| fvalue < std::numeric_limits<int>::min())
				status[TypeInt] |= notPossible;
			break;
		case TypeDouble:
			ivalue = static_cast<int>(dvalue);
			fvalue = static_cast<float>(dvalue);
			cvalue = static_cast<char>(dvalue);
			if (std::isnan(dvalue) || std::isinf(dvalue)
				|| dvalue > std::numeric_limits<int>::max()
				|| dvalue < std::numeric_limits<int>::min())
				status[TypeInt] |= notPossible;
			break;
		case TypeChar:
			ivalue = static_cast<int>(cvalue);
			fvalue = static_cast<float>(cvalue);
			dvalue = static_cast<double>(cvalue);
			break;
		}
		if ((status[TypeInt] & notPossible) || ivalue > 127 || ivalue < 0)
			status[TypeChar] |= notPossible;
		if (!(status[TypeChar] & notPossible) && !std::isprint(cvalue))
			status[TypeChar] |= notDisplayable;
	}
	else
	{
		status[TypeInt] |= notPossible;
		status[TypeFloat] |= notPossible;
		status[TypeDouble] |= notPossible;
		status[TypeChar] |= notPossible;
	}

	// Print char
	if (status[TypeChar] & notPossible)
		std::cout << "char: impossible" << std::endl;
	else if (status[TypeChar] & notDisplayable)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << cvalue << "'" << std::endl;

	// Print int
	if (status[TypeInt] & notPossible)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << ivalue << std::endl;

	// Print float
	if (status[TypeFloat] & notPossible)
		std::cout << "float: impossible" << std::endl;
	else
	{
		std::stringstream ss;
		ss << fvalue;
		std::string tmp = ss.str();
		bool isValue = !(std::isnan(fvalue) || std::isinf(fvalue));
		if (isValue && tmp.find('.') == std::string::npos)
			std::cout << "float: " << fvalue << ".0f" << std::endl;
		else
			std::cout << "float: " << fvalue << "f" << std::endl;
	}

	// Print double
	if (status[TypeDouble] & notPossible)
		std::cout << "double: impossible" << std::endl;
	else
	{
		std::stringstream ss;
		ss << dvalue;
		std::string tmp = ss.str();
		bool isValue = !(std::isnan(dvalue) || std::isinf(dvalue));
		if (isValue && tmp.find('.') == std::string::npos)
			std::cout << "double: " << dvalue << ".0" << std::endl;
		else
			std::cout << "double: " << dvalue << std::endl;
	}
}
