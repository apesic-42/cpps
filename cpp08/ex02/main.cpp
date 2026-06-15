
// main de test pour MutantStack : c'est le main du sujet
// on lance le meme code 2 fois (MutantStack puis std::list) et la sortie doit etre identique
#include <iostream>
#include <string>
#include <list> // pour le 2eme bloc qui compare avec une vraie liste
#include <stdlib.h>
#include <time.h>

#include "MutantStack.hpp"

int main(int, char**)
{
	{
		// premier bloc : avec notre MutantStack
		std::cout << "MutantStack" << std::endl;
		MutantStack<int>	mstack;

		mstack.push(5);  // push vient de std::stack, herite gratuitement
		mstack.push(17);
		std::cout << mstack.top() << std::endl; // top() = element du sommet
		mstack.pop();
		std::cout << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		//[...]
		mstack.push(0);
		// la nouveaute : on peut maintenant iterer sur le stack
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it; // on teste que les iterateurs supportent ++ et --
		--it;
		while (it != ite) // parcour classique [begin, end)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<int> s(mstack); // prouve qu'un MutantStack est copiable dans un std::stack normal (grace a l'heritage)
	}
	{
		// deuxieme bloc : meme logique mais avec std::list, doit donner la meme sortie (test du sujet)
		std::cout << "Natives lists" << std::endl;
		std::list<int>		mstack;

		mstack.push_back(5); // sur une list on utilise push_back au lieu de push
		mstack.push_back(17);
		std::cout << mstack.back() << std::endl; // back() = dernier element (equivalent du top)
		mstack.pop_back();
		std::cout << mstack.size() << std::endl;
		mstack.push_back(3);
		mstack.push_back(5);
		mstack.push_back(737);
		//[...]
		mstack.push_back(0);
		std::list<int>::iterator it = mstack.begin();
		std::list<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
	}
	return 0;
}
