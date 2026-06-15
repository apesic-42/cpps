// ex02 PmergeMe : tri Ford-Johnson (merge-insert sort) sur DEUX containers
// le sujet impose 2 containers differents pour comparer leur perf : deque et vector
#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <deque>  // 1er container demande par le sujet
# include <vector> // 2eme container demande par le sujet

class	PmergeMe
{
	private:
		// tout est en double : une version deque, une version vector
		std::deque<int>		dq;       // la sequence a trier (deque)
		std::deque<int>		dq_odd;   // l'element impair mis de cote (sans paire)
		std::deque<int>		dq_pend;  // les "pendants" en attente d'insertion
		struct timeval		dq_time;  // pour chronometrer le tri du deque
		std::vector<int>	vctr;     // la sequence a trier (vector)
		struct timeval		vctr_time;
		std::vector<int>	vctr_odd;
		std::vector<int>	vctr_pend;
	public:
		// Orthodox Canonical Form demandee par le sujet
		PmergeMe(void);
		PmergeMe(const PmergeMe &copy);
		~PmergeMe(void);
		PmergeMe	&operator=(const PmergeMe &copy);
		void				load_dq(char **argv);   // charge + trie + affiche (deque)
		void				load_vctr(char **argv); // pareil mais avec le vector
};

#endif
