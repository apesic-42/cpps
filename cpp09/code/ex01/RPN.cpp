#include <iostream>
#include <cstdlib>
#include "RPN.hpp"

RPN::RPN(void) {}
RPN::RPN(const RPN &copy) : nums(copy.nums) {}
RPN::~RPN(void) {}
RPN	&RPN::operator=(const RPN &copy)
{
	if (this != &copy)
		nums = copy.nums;
	return (*this);
}

void	RPN::add_num(int num)
{
	nums.push(num);
}

void	RPN::operation(char op)
{
	int	operand1;
	int	operand2;

	if (nums.size() < 2)
	{
		std::cerr << "Error" << std::endl;
		exit(1);
	}
	operand2 = nums.top();
	nums.pop();
	operand1 = nums.top();
	nums.pop();
	switch (op)
	{
		case '+':
			nums.push(operand1 + operand2);
			break ;
		case '-':
			nums.push(operand1 - operand2);
			break ;
		case '/':
			if (operand2 == 0)
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

int		RPN::result(void)
{
	if (nums.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		exit(1);
	}
	return (nums.top());
}
