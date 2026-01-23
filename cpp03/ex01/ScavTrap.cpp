
#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void)
{
	std::cout << "ScavTrap from ClapTrap " << this->_name << " created with default constructor." << std::endl;
	this->_name = "default";
	this->_hp	= 100;
	this->_nrj_pts	= 50;
	this->_dmg	= 20;
}

ScavTrap::ScavTrap(std::string const &name): ClapTrap(name)
{
	std::cout << "ScavTrap from ClapTrap " << this->_name << " created." << std::endl;
	this->_name = name;
	this->_hp	= 100;
	this->_nrj_pts	= 50;
	this->_dmg	= 20;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "ScavTrap from ClapTrap " << this->_name << " destroyed." << std::endl;
}

ScavTrap::ScavTrap(ScavTrap const &copy): ClapTrap(copy)
{
	std::cout << "ScavTrap from ClapTrap " << this->_name << " copied." << std::endl;
}

ScavTrap	&ScavTrap::operator=(ScavTrap const &copy)
{
	std::cout << "Assignment operator for ScavTrap called." << std::endl;
	if(this != &copy)
		ClapTrap::operator=(copy);
	return (*this);
}


void	ScavTrap::attack(const std::string& target)
{
	if (this->get_nrj_pts() > 0 && this->get_hp() > 0)
	{
		this->set_nrj_pts(this->get_nrj_pts() - 1);
		std::cout << "ScavTrap " << this->get_name()
					<< " attacks " << target
					<< " causing " << this->get_dmg()
					<< " points of damage!" << std::endl;
	}
	else
		std::cout << "ScavTrap " << this->get_name()
				<< " is too weak to attack" << std::endl;
}

void	ScavTrap::guardGate(void)
{
	if (this->_hp <= 0)
		std::cout << "Cannot switch to gate-keeper mode because: ClapTrap " << this->_name << " is dead." << std::endl;
	else
		std::cout << "ScavTrap from ClapTrap " << this->_name << " switched to mode: \"Guard Gate\"." << std::endl;
}
