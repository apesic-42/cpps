#include <algorithm>  // std::swap_ranges (autorise en module 09)
#include <iostream>
#include "PmergeMe.hpp"
#include <string>
#include <cstdlib>
#include <sys/time.h> // gettimeofday + struct timeval pour mesurer le temps

PmergeMe::PmergeMe(void) {}
// constructeur de copie : liste d'init qui recopie les 2 containers + leurs buffers
PmergeMe::PmergeMe(const PmergeMe &copy)
	: dq(copy.dq), dq_pend(copy.dq_pend), dq_time(copy.dq_time),
	  vctr(copy.vctr), vctr_pend(copy.vctr_pend), vctr_time(copy.vctr_time) {}
PmergeMe::~PmergeMe(void) {}
PmergeMe	&PmergeMe::operator=(const PmergeMe &copy)
{
	if (this != &copy) // anti auto-affectation
	{
		dq = copy.dq;
		dq_pend = copy.dq_pend;
		dq_time = copy.dq_time;
		vctr = copy.vctr;
		vctr_pend = copy.vctr_pend;
		vctr_time = copy.vctr_time;
	}
	return (*this);
}

// nombres de Jacobsthal : J(0)=0, J(1)=1, J(n)=J(n-1)+2*J(n-2)
// donne 0,1,1,3,5,11,21... ils dictent l'ordre d'insertion optimal des pendants (recursif naif mais n reste petit donc ca passe)
static unsigned int	jacobsthal(unsigned int n)
{
	if (!n)
		return (0);
	if (n == 1)
		return (1);
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

// recherche binaire sur les groupes [0, high) de la chaine. on compare item au derneir element de chaque groupe (c'est le plus grand du groupe = sacle)
// renvoie l'index du groupe devant lequel inserer (entre 0 et high inclus).
// high = borne Ford-Johnson, c'est elle qui limite le nombre de comparaisons
template <class Container>
static unsigned int	bin_search(const Container &a, int item, unsigned int high, unsigned int nb)
{
	unsigned int	low = 0;
	unsigned int	mid;

	while (low < high)
	{
		mid = (low + high) / 2;
		if (item > a[mid * nb + nb - 1]) // plus grand que la cle du groupe mid
			low = mid + 1;               // -> on cherche a droite
		else
			high = mid;                  // -> a gauche (egal = on insere devant, ok pour des int)
	}
	return (low);
}

// phase descedndante de l'algo : a chaque niveau (nb grand vers 1) la chaine est
// une suite de groupes de nb elements, triee par cle (dernier element du groupe).
//
// les groupes d'index pair (sauf le 1er) sont les "pendants" b2..bm : chacun est
// plus petit que son partenaire a_k qui lui reste dans la chaine. on les insere
// par recherche binaire dans l'ordre de Jacobsthal, puis on descend d'un niveau.
// template = un seul code pour deque et vector
template <class Container>
static void	insert(Container &cntnr, Container &pend, unsigned int nb)
{
	unsigned int	groups = cntnr.size() / nb; // nb de groupes complets
	unsigned int	tail = cntnr.size() % nb;   // elements en trop a la fin : ils ne bougent pas a ce niveau
	Container		odd;

	// 1) nombre de groupes impair : le dernier n'a pas de partenaire, on le met
	// de cote. il sera traite comme le dernier pendant (b_{m+1} chez Knuth)
	if (groups % 2)
	{
		odd.insert(odd.end(), cntnr.end() - tail - nb, cntnr.end() - tail);
		cntnr.erase(cntnr.end() - tail - nb, cntnr.end() - tail);
	}
	// 2) extraction des pendants b2, b3... = groupes 2, 4, 6... (apres chaque
	// erase le groupe suivant glisse en i, donc i += nb saute bien un groupe).
	// b1 (groupe 0) reste : il est deja plus petit que a1 donc deja a sa place
	for (unsigned int i = nb * 2; i + nb - 1 < cntnr.size() - tail; i += nb)
	{
		pend.insert(pend.end(), cntnr.begin() + i, cntnr.begin() + i + nb);
		cntnr.erase(cntnr.begin() + i, cntnr.begin() + i + nb);
	}
	pend.insert(pend.end(), odd.begin(), odd.end()); // l'impair = dernier pendant
	// 3) insertion par blocs de Jacobsthal. pend[0] = b2 donc le 1er bloc est
	// b2..b3 (J(3)-J(2) = 2 pendants), puis b4..b5, b6..b11, b12..b21...
	// dans un bloc on insere du plus grand index vers le plus petit, et la
	// recherche est limitee aux groupes devant le partenaire a_k : c'est la que
	// Ford-Johnson gagne ses comparaisons. la borne marche
	// car b_k <= a_k donc b_k ne peut pas tomber apres a_k
	unsigned int	k = 3;
	while (pend.size())
	{
		unsigned int	block = jacobsthal(k) - jacobsthal(k - 1); // taille du bloc
		unsigned int	bound;

		if (block > pend.size() / nb) // dernier bloc partiel
			block = pend.size() / nb;
		// borne de recherche en groupes = ce qu'il y a devant le partenaire du
		// plus grand pendant du bloc : b1 + ses (i-1) a + les pendants des blocs
		// precedents (J(k-1) - 1) + ceux du bloc inseres avant lui. ca donne
		// 2*J(k-1) + block - 1, soit 2^k - 1 pour un bloc complet. plafonner
		// betement a 2^k - 1 fait trop de comparaisons sur le dernier bloc
		bound = 2 * jacobsthal(k - 1) + block - 1;
		if (bound > (cntnr.size() - tail) / nb) // chaine plus courte (cas n = 1 : chaine vide)
			bound = (cntnr.size() - tail) / nb;
		for (unsigned int pos = block; pos > 0; pos--)
		{
			// cle du pendant = son dernier element, on cherche son groupe cible
			unsigned int	g = bin_search(cntnr, pend[pos * nb - 1], bound, nb);

			// on insere le groupe entier (nb elements) puis on le retire de pend
			cntnr.insert(cntnr.begin() + g * nb, pend.begin() + (pos - 1) * nb, pend.begin() + pos * nb);
			pend.erase(pend.begin() + (pos - 1) * nb, pend.begin() + pos * nb);
		}
		k++; // bloc Jacobsthal suivant
	}
	// 4) on redescend d'un niveau (groupes 2x plus petits) jusqu'a nb = 1 = tri fini
	if (nb >= 2)
		insert(cntnr, pend, nb / 2);
}

// phase MONTANTE : on travaille par groupes de taille nb, on compare les 2
// demi-groupes via leur dernier element et on met le plus grand a droite, puis
// on double nb recursivement. quand on ne peut plus doubler on bascule vers
// insert (phase descendante)
template <class Container>
static void	pairsort(Container &cntnr, Container &pend, unsigned int nb)
{
	// pour chaque groupe de nb : compare les 2 demi-groupes via leur dernier elem
	for (unsigned int i = 0; i + nb - 1 < cntnr.size(); i += nb)
		if (cntnr[i + (nb / 2) - 1] > cntnr[i + nb - 1]) // 1ere moitie > 2eme ?
			// swap les 2 demi-groupes pour mettre le plus grand a droite
			std::swap_ranges(cntnr.begin() + i, cntnr.begin() + i + (nb / 2), cntnr.begin() + i + (nb / 2));
	if (nb * 2 > cntnr.size()) // on ne peut plus doubler -> phase d'insertion
		insert(cntnr, pend, nb / 2);
	else
		pairsort(cntnr, pend, nb * 2); // sinon on double la taille
}

// temps ecoule en microsecondes depuis time. gettimeofday = precision us, suffisant
static long	time_elapsed(struct timeval time)
{
	struct timeval	new_time;

	gettimeofday(&new_time, 0);
	return ((new_time.tv_sec - time.tv_sec) * 1000000 + new_time.tv_usec - time.tv_usec);
}

// charge les args dans le deque, le trie, affiche la sequence triee + le temps
void	PmergeMe::load_dq(char **argv)
{
	long	time_store;

	gettimeofday(&dq_time, 0); // top depart du chrono (le parsing compte dedans, le sujet le dit)
	for (int i = 1; argv[i]; i++)
		dq.push_back(std::atoi(argv[i]));
	pairsort(dq, dq_pend, 2);              // lance Ford-Johnson en partant de paires
	time_store = time_elapsed(dq_time);    // stop le chrono
	std::cout << "After:"; // c'est le deque qui affiche la sequence triee
	for (unsigned int i = 0; i < dq.size(); i++)
		std::cout << " " << dq[i];
	std::cout << std::endl;
	std::cout << "Time to process a range of " << dq.size() << " elements with std::deque : " << time_store << " us" << std::endl;
}

// pareil que load_dq mais avec le vector. affiche que le temps (la seq est la meme)
void	PmergeMe::load_vctr(char **argv)
{
	gettimeofday(&vctr_time, 0);
	for (int i = 1; argv[i]; i++)
		vctr.push_back(std::atoi(argv[i]));
	pairsort(vctr, vctr_pend, 2);
	std::cout << "Time to process a range of " << vctr.size() << " elements with std::vector : " << time_elapsed(vctr_time) << " us" << std::endl;
}
