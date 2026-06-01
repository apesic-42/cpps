#ifndef RPN_HPP
# define RPN_HPP
# include <stack>

class RPN
{
	private:
		std::stack<int>	nums;
	public:
		RPN(void);
		RPN(const RPN &copy);
		~RPN(void);
		RPN	&operator=(const RPN &copy);
		void			add_num(int num);
		void			operation(char op);
		int				result(void);
};

#endif
