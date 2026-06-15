
// ex02 MutantStack : std::stack est le seul container STL pas iterable, le sujet veut le rendre iterable
// l'idee est d'heriter de std::stack et de re-exposer les iterateurs du container sous-jacent
#ifndef MUTANTSTACK_CLASS_H
# define MUTANTSTACK_CLASS_H

# include <stack> // std::stack = adaptateur de container (LIFO), encapsule un std::deque par defaut

template<typename T> // template car std::stack est template, on connait pas le type stocke
class MutantStack: public std::stack<T> { // heritage public : on recupere push, pop, top, size, empty gratis (demande par le sujet)
public:
	// orthodox canonical form
	MutantStack(void);
	MutantStack(const MutantStack<T> &src);
	~MutantStack(void);
	MutantStack<T>	&operator =(const MutantStack<T> &src);

	// le coeur du sujet : on cree des alias vers les iterateurs du container sous-jacent
	// std::stack expose un typedef container_type (le deque), qui lui a deja des iterateurs
	// typename obligatoire car c'est un type dependant du template
	typedef typename std::stack<T>::container_type::iterator		iterator;
	typedef typename std::stack<T>::container_type::const_iterator	const_iterator;

	// on fournit begin/end en const et non const pour suivre la convention STL
	iterator		begin(void);		// version modifiable
	const_iterator	begin(void) const;	// version lecture seule (appelee si l'objet est const)
	iterator		end(void);
	const_iterator	end(void) const;
};

// implementation directement dans le .hpp car c'est une classe template (doit etre visible a l'instanciation)
template<class T>
MutantStack<T>::MutantStack(void)
{
}

template<class T>
MutantStack<T>::MutantStack(const MutantStack<T> &src)
{
	*this = src;
}

template<class T>
MutantStack<T>::~MutantStack(void)
{
}

template<class T>
MutantStack<T>	&MutantStack<T>::operator =(const MutantStack<T> &src)
{
	if (this != &src)
		std::stack<T>::operator=(src); // on appelle explicitement l'operator= du parent
	// piege : si on faisait *this = src ca rappellerait MutantStack::operator= a l'infini (stack overflow)
	return *this;
}

// begin/end retournent juste les iterateurs du container sous-jacent
// this->c est le membre protege de std::stack qui contient le deque, accessible car on herite
template<class T>
typename MutantStack<T>::iterator	MutantStack<T>::begin(void)
{
	return this->c.begin(); // le deque a deja un begin(), le stack le cachait, nous on le re-expose
}

template<class T>
typename MutantStack<T>::const_iterator	MutantStack<T>::begin(void) const
{
	return this->c.begin();
}

template<class T>
typename MutantStack<T>::iterator	MutantStack<T>::end(void)
{
	return this->c.end();
}

template<class T>
typename MutantStack<T>::const_iterator	MutantStack<T>::end(void) const
{
	return this->c.end();
}

#endif
