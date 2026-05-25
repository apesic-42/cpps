

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Span.hpp"

int main(int, char**)
{
	std::cout << "Test subject main, should output (2, 14): ";
	Span sp = Span(5);
	int	array[] = {6, 3, 17, 9, 11};
	sp.insertMany(array, array + sizeof(array)/sizeof(array[0]));
	std::cout << "(" << sp.shortestSpan() << ", " << sp.longestSpan() << ")" << std::endl;

	Span	empty = Span();

	std::cout << "Trying to add number to a 0 sized span : ";
	try
	{
		empty.addNumber(42);
		std::cout << "No problem ?" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Trying to find maximum of a 0 sized span : ";
	try
	{
		empty.longestSpan();
		std::cout << "No problem ?" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Trying to find minimum of a 0 sized span : ";
	try
	{
		empty.shortestSpan();
		std::cout << "No problem ?" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Testing deep copy : ";
	Span	l1 = Span(3);
	l1.addNumber(42);
	l1.addNumber(21);
	Span	l2 = l1;
	l2.addNumber(13);
	if (l1.shortestSpan() == l2.shortestSpan())
		std::cout << "Bad deep copy !" << std::endl;
	else
		std::cout << "OK" << std::endl;
	std::cout << std::endl;

	size_t		crazy_size = 1000000;
	Span		crazy_span = Span(crazy_size);
	std::cout << "Fill a " << crazy_size << " sized span with random values." << std::endl;
	crazy_span.fillWithRandom(crazy_size);
	std::cout << "    ShortestSpan(): " << crazy_span.shortestSpan() << std::endl;
	std::cout << "    LongestSpan(): " << crazy_span.longestSpan() << std::endl;

	return 0;
}
