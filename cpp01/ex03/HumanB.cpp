


#include "HumanB.h"
#include "iostream"

void HumanB::attack()
{
    std::cout << this->name << "attacks with their" << this->weapon.getType() << std::endl;
}

void HumanB::setWeapon(Weapon weapon){
    this->weapon = weapon;
}
HumanB::HumanB(std::string name) : name(name) {}
