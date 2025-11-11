
#include "Weapon.h"

#ifndef HUMANA_HPP
#define HUMANA_HPP

class HumanA{
    private :
        Weapon weanpon;
        std::string name;

    public :
        void attack();
        // HumanA takes the Weapon in its constructor
};
#endif
