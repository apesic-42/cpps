#include <iostream>
#include <cstdlib>
#include "RPN.hpp"

int	main(int argc, char **argv)
{
	std::string	arg;
	RPN			calc;
	std::string	obj;

	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	arg = argv[1];
	arg.push_back(' ');
	while (arg[0] == ' ' || arg[0] == '\t')
		arg.erase(0, 1);
	while (arg.length())
	{
		obj = arg.substr(0, arg.find_first_of(" \t"));
		if (obj == "+" || obj == "-" || obj == "/" || obj == "*")
			calc.operation(obj[0]);
		else if (obj.length() != 1 || !std::isdigit(obj[0]))
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}
		else
			calc.add_num(obj[0] - '0');
		while (arg[0] && arg[0] != ' ' && arg[0] != '\t')
			arg.erase(0, 1);
		while (arg[0] == ' ' || arg[0] == '\t')
			arg.erase(0, 1);
	}
	std::cout << calc.result() << std::endl;
}
