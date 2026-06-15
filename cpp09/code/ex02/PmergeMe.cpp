#include <algorithm>  // std::swap_ranges (autorise en module 09)
#include <iostream>
#include "PmergeMe.hpp"
#include <string>
#include <cstdlib>    // atoi (C++98 friendly)
#include <sys/time.h> // gettimeofday + struct timeval pour mesurer le temps

PmergeMe::PmergeMe(void) {}
// constructeur de copie : liste d'init qui recopie les 2 containers + leurs buffers
PmergeMe::PmergeMe(const PmergeMe &copy)
	: dq(copy.dq), dq_odd(copy.dq_odd), dq_pend(copy.dq_pend),
	  vctr(copy.vctr), vctr_odd(copy.vctr_odd), vctr_pend(copy.vctr_pend) {}
PmergeMe::~PmergeMe(void) {}
PmergeMe	&PmergeMe::operator=(const PmergeMe &copy)
{
	if (this != &copy) // anti auto-affectation
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

// helper d'indexation : l'algo travaille par groupes de nb elements, pas par
// elements isoles. t(val, nb) donne l'index du DERNIER element du groupe val
// (le dernier d'un groupe est le plus grand, c'est lui qui sert de cle de compare)
static int			t(int val, int nb)
{
	return (val * nb + nb - 1);
}

// recherche binaire recursive : trouve ou inserer item dans le container a.
// elle compare avec le dernier element de chaque groupe (t(mid, n)) car c'est
// le representant (le plus grand) du groupe. template = meme code deque/vector
template <class Container>
static int			bin_search(Container a, int item, int low, int high, int n)
{
	int	mid;

	if (high <= low) // plus rien a couper : on est sur la position d'insertion
		return ((item > a[t(low, n)]) ? (t(low + 1, n)) : t(low, n));
    mid = (low + high) / 2;
	if (item == a[t(mid, n)]) // egal -> on insere juste apres
		return (t(mid + 1, n));
	if (item > a[t(mid, n)]) // plus grand -> on cherche dans la moitie droite
		return (bin_search(a, item, mid + 1, high, n));
	return (bin_search(a, item, low, mid - 1, n)); // sinon moitie gauche
}

// nombres de Jacobsthal : J(0)=0, J(1)=1, J(n)=J(n-1)+2*J(n-2)
// donne 0,1,1,3,5,11,21... ils dictent l'ordre d'insertion optimal des pendants
// (recursif naif mais n reste petit donc ca passe)
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

// phase DESCENDANTE de l'algo : a chaque niveau (de nb grand vers 1) on insere
// les petits elements (pendants) dans la chaine principale via Jacobsthal.
// template = un seul code pour deque et vector
template <class Container>
static Container	insert(Container cntnr, Container odd, Container pend, unsigned int nb)
{
	int				i;
	int				jacobsthal;
	unsigned int	pos;

	// 1) si le nombre de groupes est impair, on isole le dernier groupe dans odd
	if (((cntnr.size() - cntnr.size() % nb) / nb) % 2)
	{
		odd.insert(odd.begin(), cntnr.end() - cntnr.size() % nb - nb, cntnr.end() - cntnr.size() % nb);
		cntnr.erase(cntnr.end() - cntnr.size() % nb - nb, cntnr.end() - cntnr.size() % nb);
	}
	// 2) on extrait les pendants (les "petits" de chaque paire) vers pend.
	// le 1er pendant (index 0) reste car deja a sa place en tete de chaine
	for (unsigned int i = nb * 2; i + nb - 1 < cntnr.size(); i += nb)
	{
		pend.insert(pend.end(), cntnr.begin() + i, cntnr.begin() + i + nb);
		cntnr.erase(cntnr.begin() + i, cntnr.begin() + i + nb);
	}
	// 3) on insere les pendants dans l'ordre dicte par Jacobsthal (3,2,1,5,4,...)
	jacobsthal = 3;
	while (pend.size())
	{
		if (jacobsthal == 3) // amorce de la suite
			pos = 3;
		else // ecart entre 2 termes de Jacobsthal = combien de pendants ce bloc couvre
			pos = jacobsthaler(jacobsthal) - jacobsthaler(jacobsthal - 1);
		if (pos > pend.size() / nb) // plus assez de pendants pour ce bloc Jacobsthal
		{
			// on vide alors les pendants restants un par un (du 1er vers le dernier)
			while (pend.size())
			{
				// cherche la position d'insertion du pendant (sa cle = dernier elem)
				i = bin_search(cntnr, pend[nb - 1], 0, cntnr.size() / nb, nb);
				// std::cout << "1st item to displace: " << *(cntnr.begin() + i - (nb - 1)) << ", i: " << i << ", nb: " << nb << ", item: " << pend[nb - 1] << std::endl;
				// print(cntnr, odd, pend);
				// garde fou si la position calculee depasse la fin du container
				if (cntnr.begin() + i - (nb - 1) > cntnr.end())
					cntnr.insert(cntnr.end() - cntnr.size() % nb, pend.begin(), pend.begin() + nb);
				else // insere le groupe entier (nb elements) a sa place
					cntnr.insert(cntnr.begin() + i - (nb - 1), pend.begin(), pend.begin() + nb);
				pend.erase(pend.begin(), pend.begin() + nb); // retire le pendant traite
			}
			break ;
		}
		// insertion dans l'ordre Jacobsthal : du pendant pos vers le 1er (decroissant)
		while (pos)
		{
			i = bin_search(cntnr, pend[nb * pos - 1], 0, cntnr.size() / nb, nb);
			// std::cout << "1st item to displace: " << *(cntnr.begin() + i - (nb - 1)) << ", i: " << i << ", nb: " << nb << ", item: " << pend[pos * nb - 1] << std::endl;
			// print(cntnr, odd, pend);
			if (cntnr.begin() + i - (nb - 1) > cntnr.end()) // meme garde fou
				cntnr.insert(cntnr.end() - cntnr.size() % nb, pend.begin() + pos * nb - nb, pend.begin() + pos * nb);
			else
				cntnr.insert(cntnr.begin() + i - (nb - 1), pend.begin() + pos * nb - nb, pend.begin() + pos * nb);
			pend.erase(pend.begin() + pos * nb - nb, pend.begin() + pos * nb);
			pos--;
		}
		jacobsthal++; // bloc Jacobsthal suivant
	}
	// 4) si on avait isole un element impair, on l'insere lui aussi par recherche binaire
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
	// 5) on redescend d'un niveau (groupes 2x plus petits) jusqu'a nb=1 = tri fini
	if (nb >= 2)
		return (insert(cntnr, odd, pend, nb / 2));
	return (cntnr); // nb < 2 : la sequence est triee, on la rend
}

// phase MONTANTE : on travaille par groupes de taille nb, on trie chaque paire
// de demi-groupes (le plus grand a droite) puis on double nb recursivement.
// quand on ne peut plus doubler on bascule vers insert (phase descendante)
template <class Container>
static Container	pairsort(Container cntnr, Container odd, Container pend,unsigned int nb)
{
	// pour chaque groupe de nb : compare les 2 demi-groupes via leur dernier elem
	for (unsigned int i = 0; i + nb - 1 < cntnr.size(); i += nb)
		if (cntnr[i + (nb / 2) - 1] > cntnr[i + nb - 1]) // 1ere moitie > 2eme ?
			// swap les 2 demi-groupes pour mettre le plus grand a droite
			std::swap_ranges(cntnr.begin() + i, cntnr.begin() + i + (nb / 2), cntnr.begin() + i + (nb / 2));
	if (nb * 2 > cntnr.size()) // on ne peut plus doubler -> phase d'insertion
		return (insert(cntnr, odd, pend, nb / 2));
	return (pairsort(cntnr, odd, pend, nb * 2)); // sinon on double la taille
}

// temps ecoule en microsecondes depuis time. gettimeofday = precision us, suffisant
static long			time_elapsed(struct timeval time)
{
	struct timeval	new_time;

	gettimeofday(&new_time, 0);
	return ((new_time.tv_sec - time.tv_sec) * 1000000 + new_time.tv_usec - time.tv_usec);
}

// charge les args dans le deque, le trie, affiche la sequence triee + le temps
void				PmergeMe::load_dq(char **argv)
{
	long	time_store;

	gettimeofday(&dq_time, 0); // top depart du chrono (le parsing compte dedans)
	for (int i = 1; argv[i]; i++)
		dq.push_back(atoi(argv[i])); // atoi = conversion C++98 friendly
	dq = pairsort(dq, dq_odd, dq_pend, 2); // lance Ford-Johnson en partant de paires
	time_store = time_elapsed(dq_time);    // stop le chrono
	std::cout << "After:"; // c'est le deque qui affiche la sequence triee
	for (unsigned int i = 0; i < dq.size(); i++)
		std::cout << " " << dq[i];
	std::cout << std::endl;
	std::cout << "Time to process a range of " << dq.size() << " elements with std::deque : " << time_store << " us" << std::endl;
}

// pareil que load_dq mais avec le vector. affiche que le temps (la seq est la meme)
void				PmergeMe::load_vctr(char **argv)
{
	gettimeofday(&vctr_time, 0);
	for (int i = 1; argv[i]; i++)
		vctr.push_back(atoi(argv[i]));
	vctr = pairsort(vctr, vctr_odd, vctr_pend, 2);
	std::cout << "Time to process a range of " << vctr.size() << " elements with std::vector : " << time_elapsed(vctr_time) << " us" << std::endl;
}
