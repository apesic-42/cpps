
#include <iostream>
#include "ScalarConverter.hpp"

int main(int argc, char const *argv[])
{
	if (argc != 2)
		std::cout << "convert: bad arguments!" << std::endl;
	else
		ScalarConverter::convert(argv[1]);
	return (0);
}
