
#include "Zombie.hpp"
#include <string>
#include <iostream>

using namespace std;


void Zombie::announce(void)
{
    cout << this->name << ": BraiiiiiiinnnzzzZ..." << endl;
}



Zombie::Zombie() : name("Nameless") {
    std::cout << "Zombie created (default): " << name << std::endl;
}

Zombie::Zombie(std::string name) : name(name) {
    std::cout << "Zombie created: " << name << std::endl;
}

Zombie::~Zombie() {
    // delete this;
    std::cout << "Zombie destroyed: " << name << std::endl;
}
