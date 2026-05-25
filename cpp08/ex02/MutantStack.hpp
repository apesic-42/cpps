
#ifndef MUTANTSTACK_CLASS_H
# define MUTANTSTACK_CLASS_H

# include <stack>

template<typename T>
class MutantStack: public std::stack<T> {
public:
	MutantStack(void);
	MutantStack(const MutantStack<T> &src);
	~MutantStack(void);
	MutantStack<T>	&operator =(const MutantStack<T> &src);

	typedef typename std::stack<T>::container_type::iterator		iterator;
	typedef typename std::stack<T>::container_type::const_iterator	const_iterator;

	iterator		begin(void);
	const_iterator	begin(void) const;
	iterator		end(void);
	const_iterator	end(void) const;
};

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
		std::stack<T>::operator=(src);
	return *this;
}

template<class T>
typename MutantStack<T>::iterator	MutantStack<T>::begin(void)
{
	return this->c.begin();
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
