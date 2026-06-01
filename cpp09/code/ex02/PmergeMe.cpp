#include <algorithm>
#include <iostream>
#include "PmergeMe.hpp"
#include <string>
#include <cstdlib>
#include <sys/time.h>

PmergeMe::PmergeMe(void) {}
PmergeMe::PmergeMe(const PmergeMe &copy)
	: dq(copy.dq), dq_odd(copy.dq_odd), dq_pend(copy.dq_pend),
	  vctr(copy.vctr), vctr_odd(copy.vctr_odd), vctr_pend(copy.vctr_pend) {}
PmergeMe::~PmergeMe(void) {}
PmergeMe	&PmergeMe::operator=(const PmergeMe &copy)
{
	if (this != &copy)
	{
		dq = copy.dq;
		dq_odd = copy.dq_odd;
		dq_pend = copy.dq_pend;
		vctr = copy.vctr;
		vctr_odd = copy.vctr_odd;
		vctr_pend = copy.vctr_pend;
	}
	return (*this);
}

static int			t(int val, int nb)
{
	return (val * nb + nb - 1);
}

template <class Container>
static int			bin_search(Container a, int item, int low, int high, int n)
{
	int	mid;

	if (high <= low)
		return ((item > a[t(low, n)]) ? (t(low + 1, n)) : t(low, n));
    mid = (low + high) / 2;
	if (item == a[t(mid, n)])
		return (t(mid + 1, n));
	if (item > a[t(mid, n)])
		return (bin_search(a, item, mid + 1, high, n));
	return (bin_search(a, item, low, mid - 1, n));
}

int					jacobsthaler(int n)
{
	if (!n)
		return (0);
    if (n == 1)
		return (1);
    return (jacobsthaler(n - 1) + 2 * jacobsthaler(n - 2));
}

// template <class Container>
// static void			print(Container cntnr, Container odd, Container pend)
// {
// 	std::cout << "cntnr:";
// 	for (unsigned int i = 0; i < cntnr.size(); i++)
// 		std::cout << " " << cntnr[i];
// 	std::cout << std::endl;
// 	std::cout << "pend:";
// 	for (unsigned int i = 0; i < pend.size(); i++)
// 		std::cout << " " << pend[i];
// 	std::cout << std::endl;
// 	std::cout << "odd:";
// 	for (unsigned int i = 0; i < odd.size(); i++)
// 		std::cout << " " << odd[i];
// 	std::cout << std::endl;
// }

template <class Container>
static Container	insert(Container cntnr, Container odd, Container pend, unsigned int nb)
{
	int				i;
	int				jacobsthal;
	unsigned int	pos;

	if (((cntnr.size() - cntnr.size() % nb) / nb) % 2)
	{
		odd.insert(odd.begin(), cntnr.end() - cntnr.size() % nb - nb, cntnr.end() - cntnr.size() % nb);
		cntnr.erase(cntnr.end() - cntnr.size() % nb - nb, cntnr.end() - cntnr.size() % nb);
	}
	for (unsigned int i = nb * 2; i + nb - 1 < cntnr.size(); i += nb)
	{
		pend.insert(pend.end(), cntnr.begin() + i, cntnr.begin() + i + nb);
		cntnr.erase(cntnr.begin() + i, cntnr.begin() + i + nb);
	}
	jacobsthal = 3;
	while (pend.size())
	{
		if (jacobsthal == 3)
			pos = 3;
		else
			pos = jacobsthaler(jacobsthal) - jacobsthaler(jacobsthal - 1);
		if (pos > pend.size() / nb)
		{
			while (pend.size())
			{
				i = bin_search(cntnr, pend[nb - 1], 0, cntnr.size() / nb, nb);
				// std::cout << "1st item to displace: " << *(cntnr.begin() + i - (nb - 1)) << ", i: " << i << ", nb: " << nb << ", item: " << pend[nb - 1] << std::endl;
				// print(cntnr, odd, pend);
				if (cntnr.begin() + i - (nb - 1) > cntnr.end())
					cntnr.insert(cntnr.end() - cntnr.size() % nb, pend.begin(), pend.begin() + nb);
				else
					cntnr.insert(cntnr.begin() + i - (nb - 1), pend.begin(), pend.begin() + nb);
				pend.erase(pend.begin(), pend.begin() + nb);
			}
			break ;
		}
		while (pos)
		{
			i = bin_search(cntnr, pend[nb * pos - 1], 0, cntnr.size() / nb, nb);
			// std::cout << "1st item to displace: " << *(cntnr.begin() + i - (nb - 1)) << ", i: " << i << ", nb: " << nb << ", item: " << pend[pos * nb - 1] << std::endl;
			// print(cntnr, odd, pend);
			if (cntnr.begin() + i - (nb - 1) > cntnr.end())
				cntnr.insert(cntnr.end() - cntnr.size() % nb, pend.begin() + pos * nb - nb, pend.begin() + pos * nb);
			else
				cntnr.insert(cntnr.begin() + i - (nb - 1), pend.begin() + pos * nb - nb, pend.begin() + pos * nb);
			pend.erase(pend.begin() + pos * nb - nb, pend.begin() + pos * nb);
			pos--;
		}
		jacobsthal++;
	}
	if (odd.size())
	{
		i = bin_search(cntnr, odd[nb - 1], 0, cntnr.size() / nb, nb);
		// std::cout << "1st item to displace: " << *(cntnr.begin() + i - (nb - 1)) << ", i: " << i << ", nb: " << nb << ", item: " << odd[nb - 1] << std::endl;
		// print(cntnr, odd, pend);
		if (cntnr.begin() + i - (nb - 1) > cntnr.end())
			cntnr.insert(cntnr.end() - cntnr.size() % nb, odd.begin(), odd.begin() + nb);
		else
			cntnr.insert(cntnr.begin() + i - (nb - 1), odd.begin(), odd.begin() + nb);
		odd.clear();
	}
	// std::cout << "completed iteration " << nb << std::endl;
	// print(cntnr, odd, pend);
	if (nb >= 2)
		return (insert(cntnr, odd, pend, nb / 2));
	return (cntnr);
}

template <class Container>
static Container	pairsort(Container cntnr, Container odd, Container pend,unsigned int nb)
{
	for (unsigned int i = 0; i + nb - 1 < cntnr.size(); i += nb)
		if (cntnr[i + (nb / 2) - 1] > cntnr[i + nb - 1])
			std::swap_ranges(cntnr.begin() + i, cntnr.begin() + i + (nb / 2), cntnr.begin() + i + (nb / 2));
	if (nb * 2 > cntnr.size())
		return (insert(cntnr, odd, pend, nb / 2));
	return (pairsort(cntnr, odd, pend, nb * 2));
}

static long			time_elapsed(struct timeval time)
{
	struct timeval	new_time;

	gettimeofday(&new_time, 0);
	return ((new_time.tv_sec - time.tv_sec) * 1000000 + new_time.tv_usec - time.tv_usec);
}

void				PmergeMe::load_dq(char **argv)
{
	long	time_store;

	gettimeofday(&dq_time, 0);
	for (int i = 1; argv[i]; i++)
		dq.push_back(atoi(argv[i]));
	dq = pairsort(dq, dq_odd, dq_pend, 2);
	time_store = time_elapsed(dq_time);
	std::cout << "After:";
	for (unsigned int i = 0; i < dq.size(); i++)
		std::cout << " " << dq[i];
	std::cout << std::endl;
	std::cout << "Time to process a range of " << dq.size() << " elements with std::deque : " << time_store << " us" << std::endl;
}

void				PmergeMe::load_vctr(char **argv)
{
	gettimeofday(&vctr_time, 0);
	for (int i = 1; argv[i]; i++)
		vctr.push_back(atoi(argv[i]));
	vctr = pairsort(vctr, vctr_odd, vctr_pend, 2);
	std::cout << "Time to process a range of " << vctr.size() << " elements with std::vector : " << time_elapsed(vctr_time) << " us" << std::endl;
}
