


#include "HumanA.h"
#include "iostream"

void HumanA::attack()
{
    std::cout << this->name << "attacks with their" << this->weanpon.getType() << std::endl;
}
