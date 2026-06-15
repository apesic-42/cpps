// ex01 RPN (Reverse Polish Notation) : le sujet impose un container, ici std::stack
// la stack est un LIFO, parfait pour evaluer une expression postfixee
#ifndef RPN_HPP
# define RPN_HPP
# include <stack> // le container demande, expose juste push/pop/top/size

class RPN
{
	private:
		// pile d'entiers : on empile les nombres, on depile pour les operations
		std::stack<int>	nums;
	public:
		// Orthodox Canonical Form (ctor, copy, dtor, =) demandee par le sujet
		RPN(void);
		RPN(const RPN &copy);
		~RPN(void);
		RPN	&operator=(const RPN &copy);
		void			add_num(int num);   // empile un nombre
		void			operation(char op); // depile 2, calcule, rempile
		int				result(void);       // recupere le resultat final
};

#endif
