
#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void): _name("default"), _hp(100), _nrj_pts(100), _dmg(30)
{
	std::cout << "ClapTrap " << this->_name << " created with default constructor." << std::endl;
}

ClapTrap::ClapTrap(std::string const &name): _name(name), _hp(100), _nrj_pts(100), _dmg(30)
{
	std::cout << "ClapTrap " << this->_name << " created." << std::endl;
}

ClapTrap::~ClapTrap(void)
{
	std::cout << "ClapTrap " << this->_name << " destroyed." << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const &copy)
{
	std::cout << "ClapTrap " << this->_name << " copied." << std::endl;
	*this = copy;
}

void	ClapTrap::attack(std::string const &target)
{
	if (this->_nrj_pts && this->_hp > 0)
	{
		std::cout << "ClapTrap " << this->_name << " attacked " << target << ", causing " << this->_dmg << " point(s) of damage" << std::endl;
		this->_nrj_pts--;
	}
	if (this->_hp <= 0)
		std::cout << "ClapTrap " << this->_name << " is dead" << std::endl;
	else if (!this->_nrj_pts)
		std::cout << "ClapTrap " << this->_name << " is out of energy points" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_hp > 0)
	{
		std::cout << "ClapTrap " << this->_name << " took " << amount << " point(s) of damage" << std::endl;
		this->_hp -= amount;
	}
	else
		std::cout << "STOP! ClapTrap " << this->_name << " is already dead :(" << std::endl;
	if (this->_hp < 0)
		this->_hp = 0;

}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_hp > 0 && this->_nrj_pts)
	{
		std::cout << "ClapTrap " << this->_name << " healed " << amount << " point(s)." << std::endl;
		this->_hp += amount;
		this->_nrj_pts--;
	}
	if (this->_hp <= 0)
		std::cout << "Cannot repair because: ClapTrap " << this->_name << " is dead." << std::endl;
	else if (!this->_nrj_pts)
		std::cout << "ClapTrap " << this->_name << " is out of energy points" << std::endl;
}

ClapTrap	&ClapTrap::operator=(const ClapTrap &copy)
{
	std::cout << "Assignment operator For ClapTrap called." << std::endl;
	this->_name = copy.get_name();
	this->_hp = copy.get_hp();
	this->_nrj_pts = copy.get_nrj_pts();
	this->_dmg = copy.get_dmg();
	return (*this);
}

std::string const	&ClapTrap::get_name(void) const
{
	return (this->_name);
}

int const	&ClapTrap::get_hp(void) const
{
	return (this->_hp);
}

int const	&ClapTrap::get_nrj_pts(void) const
{
	return (this->_nrj_pts);
}

int const	&ClapTrap::get_dmg(void) const
{
	return (this->_dmg);
}

void	ClapTrap::set_name(std::string const &name)
{
	this->_name = name;
}

void	ClapTrap::set_hp(int const &value)
{
	this->_hp = value;
}

void	ClapTrap::set_nrj_pts(int const &value)
{
	this->_nrj_pts = value;
}

void	ClapTrap::set_dmg(int const &value)
{
	this->_dmg = value;
}
