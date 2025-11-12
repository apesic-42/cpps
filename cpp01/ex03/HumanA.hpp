
#include "Weapon.h"

#ifndef HUMANA_HPP
#define HUMANA_HPP

class HumanA{
    private :
        std::string name;
        Weapon weapon;

    public :
        void attack();
        // HumanA takes the Weapon in its constructor
        HumanA(std::string name, Weapon weapon);
};
#endif
