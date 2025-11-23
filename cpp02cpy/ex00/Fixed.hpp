
#ifndef FIXED_HPP
# define FIXED_HPP
# include <iostream>

class Fixed
{
	private:
		int					pf;

	public:
		Fixed(void);
		Fixed(const Fixed &fixed);
		~Fixed();
		Fixed	&operator=(const Fixed&fixed);

		int		getRawBits(void) const;
		void	setRawBits(const int raw);
};

#endif
