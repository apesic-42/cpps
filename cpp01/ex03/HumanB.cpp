


#include "HumanB.h"
#include "iostream"

void HumanB::attack()
{
    std::cout << this->name << "attacks with their" << this->weanpon.getType() << std::endl;
}
