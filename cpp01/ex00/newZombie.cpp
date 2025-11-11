
#include "Zombie.hpp"
#include <string>
#include <iostream>




Zombie* newZombie(std::string name )
{
    return new Zombie(name);
}
