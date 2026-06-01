#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <deque>
# include <vector>

class	PmergeMe
{
	private:
		std::deque<int>		dq;
		std::deque<int>		dq_odd;
		std::deque<int>		dq_pend;
		struct timeval		dq_time;
		std::vector<int>	vctr;
		struct timeval		vctr_time;
		std::vector<int>	vctr_odd;
		std::vector<int>	vctr_pend;
	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe &copy);
		~PmergeMe(void);
		PmergeMe	&operator=(const PmergeMe &copy);
		void				load_dq(char **argv);
		void				load_vctr(char **argv);
};

#endif
