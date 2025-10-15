
#include "Zombie.hpp"
#include <string>
#include <iostream>

using namespace std;



Zombie* newZombie(string name )
{
    return new Zombie(name);
}
