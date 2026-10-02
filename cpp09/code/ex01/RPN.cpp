#include <iostream>
#include <cstdlib> // exit
#include <climits> // INT_MIN / INT_MAX pour detecter l'overflow
#include "RPN.hpp"

RPN::RPN(void) {}
RPN::RPN(const RPN &copy) : nums(copy.nums) {} // liste d'init : copie la stack
RPN::~RPN(void) {}
RPN	&RPN::operator=(const RPN &copy)
{
	if (this != &copy)
		nums = copy.nums;
	return (*this);
}

// empile un nombre sur la pile (cas d'un token chiffre)
void	RPN::add_num(int num)
{
	nums.push(num);
}

// applique un operateur : depile 2 operandes, calcule, rempile le resultat
void	RPN::operation(char op)
{
	long	operand1;
	long	operand2;
	long	result;

	if (nums.size() < 2) // un operateur a besoin de 2 operandes sinon expr invalide
	{
		std::cerr << "Error" << std::endl; // le sujet veut les erreurs sur stderr
		exit(1);
	}
	operand2 = nums.top();
	nums.pop();
	operand1 = nums.top(); // celui en dessous est le 1er operande
	nums.pop();
	switch (op)
	{
		case '+':
			result = operand1 + operand2;
			break ;
		case '-':
			result = operand1 - operand2;
			break ;
		case '*':
			result = operand1 * operand2;
			break ;
		default: // forcement '/' (le main a deja filtre les tokens)
			if (operand2 == 0) // division par zero = crash (SIGFPE), on protege
			{
				std::cerr << "Error" << std::endl;
				exit(1);
			}
			result = operand1 / operand2;
	}
	// on calcule en long (64 bits) puis on verifie que ca tient dans un int :
	if (result > INT_MAX || result < INT_MIN)
	{
		std::cerr << "Error" << std::endl;
		exit(1);
	}
	nums.push(result);
}

// recupere le resultat : a la fin il doit rester pile 1 element sur la pile
int		RPN::result(void)
{
	if (nums.size() != 1) // sinon l'expression etait mal formee
	{
		std::cerr << "Error" << std::endl;
		exit(1);
	}
	return (nums.top());
}
