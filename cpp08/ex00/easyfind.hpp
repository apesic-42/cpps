
#ifndef EASYFIND_H
# define EASYFIND_H

# include <algorithm>

template<typename T>
typename T::iterator	easyfind(T &elems, int el)
{
	return std::find(elems.begin(), elems.end(), el);
}

#endif
