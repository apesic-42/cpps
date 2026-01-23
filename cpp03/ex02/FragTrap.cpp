
#include "FragTrap.hpp"

FragTrap::FragTrap(void)
{
	std::cout << "FragTrap from ClapTrap " << this->_name << " created with default constructor." << std::endl;
	this->_name = "default";
	this->_hp = 100;
	this->_nrj_pts = 100;
	this->_dmg = 30;
}

FragTrap::FragTrap(std::string const &name): ClapTrap(name)
{
	std::cout << "FragTrap from ClapTrap " << this->_name << " created." << std::endl;
	this->_name = "default";
	this->_hp = 100;
	this->_nrj_pts = 100;
	this->_dmg = 30;
}

FragTrap::~FragTrap(void)
{
	std::cout << "FragTrap from ClapTrap " << this->_name << " destroyed." << std::endl;
}

FragTrap::FragTrap(FragTrap const &copy): ClapTrap(copy)
{
	std::cout << "FragTrap from ClapTrap " << this->_name << " copied." << std::endl;
}

FragTrap	&FragTrap::operator=(FragTrap const &copy)
{
	std::cout << "Assignment operator for FragTrap called." << std::endl;
	if(this != &copy)
	{
		this->set_name(copy.get_name());
		this->set_hp(copy.get_hp());
		this->set_nrj_pts(copy.get_nrj_pts());
		this->set_dmg(copy.get_dmg());
	}
	return (*this);
}

void	FragTrap::highFivesGuys(void)
{
	if (this->_hp <= 0)
		std::cout << "Cannot high five because: ClapTrap " << this->_name << " is dead." << std::endl;
	else
		std::cout << "FragTrap from ClapTrap " << this->_name << " says: \"HIGH FIVE EVERYONE! :)\"." << std::endl;
}
