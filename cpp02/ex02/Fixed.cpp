
#include "Fixed.hpp"

Fixed::Fixed(void) : pf(0)
{
	if (CALL_LOG)
		std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &fixed)
{
	if (CALL_LOG)
		std::cout << "Copy constructor called" << std::endl;
	*this = fixed;
}

Fixed::Fixed(const int n) : pf(n << nbf)
{
	if (CALL_LOG)
		std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float f) : pf((int)roundf(f * (1 << nbf)))
{
	if (CALL_LOG)
		std::cout << "Float constructor called" << std::endl;
}

Fixed::~Fixed()
{
	if (CALL_LOG)
		std::cout << "Destructor called" << std::endl;
}

Fixed	&Fixed::operator=(const Fixed &fixed)
{
	if (CALL_LOG)
		std::cout << "Copy assignment operator called" << std::endl;
	if (this != &fixed)
		this->pf = fixed.getRawBits();
	return (*this);
}

int	Fixed::getRawBits(void) const
{
	if (CALL_LOG)
		std::cout << "getRawBits member function called" << std::endl;
	return (this->pf);
}

void	Fixed::setRawBits(const int raw)
{
	if (CALL_LOG)
		std::cout << "setRawBits member function called" << std::endl;
	this->pf = raw;
}

float	Fixed::toFloat(void) const
{
	return ((float)pf / (1 << nbf));
}

int	Fixed::toInt(void) const
{
	return ((int)(roundf((float)pf / (1 << nbf))));
}

std::ostream	&operator<<(std::ostream &o, const Fixed &fixed)
{
	o << fixed.toFloat();
	return (o);
}

bool	Fixed::operator>(const Fixed &fixed) const
{
	return (this->pf > fixed.pf);
}

bool	Fixed::operator<(const Fixed &fixed) const
{
	return (this->pf < fixed.pf);
}

bool	Fixed::operator>=(const Fixed &fixed) const
{
	return (this->pf >= fixed.pf);
}

bool	Fixed::operator<=(const Fixed &fixed) const
{
	return (this->pf <= fixed.pf);
}

bool	Fixed::operator==(const Fixed &fixed) const
{
	return (this->pf == fixed.pf);
}

bool	Fixed::operator!=(const Fixed &fixed) const
{
	return (this->pf != fixed.pf);
}

Fixed	Fixed::operator+(const Fixed &fixed) const
{
	return (Fixed(this->toFloat() + fixed.toFloat()));
}

Fixed	Fixed::operator-(const Fixed &fixed) const
{
	return (Fixed(this->toFloat() - fixed.toFloat()));
}

Fixed	Fixed::operator*(const Fixed &fixed) const
{
	return (Fixed(this->toFloat() * fixed.toFloat()));
}

Fixed	Fixed::operator/(const Fixed &fixed) const
{
	return (Fixed(this->toFloat() / fixed.toFloat()));
}

Fixed	&Fixed::operator++(void)
{
	++(this->pf);
	return (*this);
}

Fixed	&Fixed::operator--(void)
{
	--(this->pf);
	return (*this);
}

Fixed Fixed::operator++( int )
{
	Fixed temp = *this;
	++*this;
	return temp;
}

Fixed Fixed::operator--( int )
{
	Fixed temp = *this;
	--*this;
	return temp;
}

Fixed	&Fixed::min(Fixed &fixed1, Fixed &fixed2)
{
	if (CALL_LOG)
		std::cout << "Static min function called" << std::endl;
	if (fixed1 <= fixed2)
		return (fixed1);
	return (fixed2);
}

Fixed	&Fixed::max(Fixed &fixed1, Fixed &fixed2)
{
	if (CALL_LOG)
		std::cout << "Static max function called" << std::endl;
	if (fixed1 >= fixed2)
		return (fixed1);
	return (fixed2);
}

const Fixed	&Fixed::min(const Fixed &fixed1, const Fixed &fixed2)
{
	if (CALL_LOG)
		std::cout << "Static const min overload called" << std::endl;
	if (fixed1 <= fixed2)
		return (fixed1);
	return (fixed2);
}

const Fixed	&Fixed::max(const Fixed &fixed1, const Fixed &fixed2)
{
	if (CALL_LOG)
		std::cout << "Static const max overload called" << std::endl;
	if (fixed1 >= fixed2)
		return (fixed1);
	return (fixed2);
}
