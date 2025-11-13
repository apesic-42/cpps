
// #include "Zombie.hpp"
#include "Zombie.h"
#include <string>
#include <iostream>
// using namespace std;



void randomChump( std::string name )
{
    Zombie* zom = newZombie(name); //pas alloc
    zom->announce();
}
