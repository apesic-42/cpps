#include <iostream>
#include <cstdlib> // exit
#include "RPN.hpp"

RPN::RPN(void) {}
RPN::RPN(const RPN &copy) : nums(copy.nums) {} // liste d'init : copie la stack
RPN::~RPN(void) {}
RPN	&RPN::operator=(const RPN &copy)
{
	if (this != &copy) // garde anti auto-affectation
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
	int	operand1;
	int	operand2;

	if (nums.size() < 2) // un operateur a besoin de 2 operandes sinon expr invalide
	{
		std::cerr << "Error" << std::endl; // le sujet veut les erreurs sur stderr
		exit(1);
	}
	// attention a l'ordre : le top de la pile est le 2eme operande
	operand2 = nums.top();
	nums.pop();
	operand1 = nums.top(); // celui en dessous est le 1er operande
	nums.pop();
	switch (op)
	{
		case '+':
			nums.push(operand1 + operand2);
			break ;
		case '-':
			nums.push(operand1 - operand2); // ordre important : 1 - 2 pas 2 - 1
			break ;
		case '/':
			if (operand2 == 0) // division par zero = crash (SIGFPE), on protege
			{
				std::cerr << "Error" << std::endl;
				exit(1);
			}
			nums.push(operand1 / operand2);
			break ;
		case '*':
			nums.push(operand1 * operand2);
			break ;
	}
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
