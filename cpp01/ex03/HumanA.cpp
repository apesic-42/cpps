


#include "HumanA.h"
#include "iostream"

void HumanA::attack()
{
    std::cout << this->name << " attacks with their " << this->weapon.getType() << std::endl;
}


HumanA::HumanA(std::string name, Weapon weapon) :name(name), weapon(weapon) {}
