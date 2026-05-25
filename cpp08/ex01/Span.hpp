
#ifndef SPAN_CLASS_H
# define SPAN_CLASS_H

# include <vector>
# include <algorithm>

class Span {
private:
	const unsigned int	_max_size;
	std::vector<int>	_elems;

public:
	Span(void);
	Span(const unsigned int max_size);
	Span(const Span &src);
	~Span(void);
	Span	&operator =(const Span &src);

	void	addNumber(const int num);
	int		shortestSpan(void) const;
	int		longestSpan(void) const;

	template<typename InputIt>
	void	insertMany(InputIt begin, InputIt end)
	{
		while (begin != end)
		{
			this->addNumber(*begin);
			++begin;
		}
	}
	void	fillWithRandom(size_t num);

	class MaxSizeReachedException: public std::exception {
	public:
		virtual const char* what(void) const throw();
	};

	class EmptySpanException: public std::exception {
	public:
		virtual const char* what(void) const throw();
	};
};

#endif
