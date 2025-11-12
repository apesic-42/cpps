

#include "Weapon.h"

#ifndef HUMANB_HPP
#define HUMANB_HPP

class HumanB{
    private :
        Weapon weapon;
        std::string name;

    public :
        void attack();
        // HumanA don't takes the Weapon in its constructor
        HumanB(std::string name);
        void setWeapon(Weapon weapon);
};
#endif
