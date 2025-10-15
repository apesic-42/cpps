

#include "Zombie.hpp"
#include "newZombie.cpp"
#include <string>
#include <iostream>
using namespace std;



void randomChump( string name )
{
    Zombie* zom = newZombie(name);
    zom->annonce();
}
