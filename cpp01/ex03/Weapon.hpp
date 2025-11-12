
#include <string>

#ifndef WEAPON_HPP
#define WEAPON_HPP


class Weapon {

    private :
        std::string type;

    public :
        std::string getType();
        void setType(std::string type);
        Weapon();
        Weapon(std::string type);
 };

#endif
