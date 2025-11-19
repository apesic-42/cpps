


#include "HumanB.h"
#include "iostream"

void HumanB::attack()
{
    if (this->weapon.getType() == "")
        std::cout << this->name << " attacks with their hands" << std::endl;
    else
        std::cout << this->name << " attacks with their " << this->weapon.getType() << std::endl;
}

void HumanB::setWeapon(Weapon weapon){
    this->weapon = weapon;
}
HumanB::HumanB(std::string name) : name(name) {}
